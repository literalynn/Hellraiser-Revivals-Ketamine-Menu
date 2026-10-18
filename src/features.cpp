#include "features.h"
#include "config.h"
#include "lang.h"
#include "log.h"
#include "menu.h"
#include "text.h"
#include "ue.h"

#include <windows.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
#include <mutex>

using namespace ue;

namespace feat {

const ToggleInfo kToggles[ToggleCount] = {
    {"GodMode", "God mode", "Health stays full and damage is ignored."},
    {"InfiniteHealth", "Infinite health", "Health refills instantly. You still take the hits."},
    {"NoSprintCooldown", "No sprint cooldown", "The game has no stamina: this removes the pause between sprints."},
    {"OneHitKill", "One-hit kill", "Any damage you deal kills the enemy. Bosses with scripted phases may resist."},
    {"Invisible", "Invisible to enemies", "Uses the developers' invisibility cheat."},
    {"InfiniteAmmo", "Infinite ammo", "Your magazine never empties, so you never reload."},
    {"NoSufferingCost", "Powers cost nothing", "Genesis Configuration powers use no Suffering, and it stays full."},
    {"NoPowerCooldown", "No power cooldown", "Removes telekinesis and pyrokinesis cooldowns."},
    {"Unbreakable", "Unbreakable melee weapons", "Melee weapons never lose durability."},
    {"Fly", "Fly", "Flies where you look, with your usual movement keys or stick."},
    {"Noclip", "Noclip", "Fly through walls, where you look, with your usual movement keys."},
    {"FreezeAI", "Freeze enemies", "Enemies stop moving and attacking."},
    {"HideHUD", "Hide HUD", "Hides the game interface (menus you open later stay visible)."},
    {"FreeCam", "Free camera", "Detached camera: movement keys to move, mouse to look. Your character stays in place."},
    {"AutoLockpick", "Auto lockpick", "Locks open by themselves a moment after you start picking them."},
    {"SkipIntros", "Skip intros",
     "Skips the logos and notices when the game starts. The EULA and brightness screens still show the first time."},
    {"Esp", "ESP", "Shows enemies and objects through walls."},
    {"EspBox", "Box", "Corner box around each enemy.", true},
    {"EspHealth", "Health bar", "Enemy health next to the box.", true},
    {"EspName", "Name", "Enemy type.", true},
    {"EspDistance", "Distance", "Distance in metres.", true},
    {"EspSkeleton", "Skeleton", "Bones drawn over the body."},
    {"EspHead", "Head marker", "Glowing dot on the head."},
    {"EspChams", "Chams", "Glowing body silhouette, visible through walls."},
    {"EspSnaplines", "Snaplines", "Lines from the bottom of the screen to each enemy."},
    {"EspOffscreen", "Off-screen arrows", "Arrows at the edge of the screen pointing at enemies you can't see.", true},
    {"EspItems", "Items on the ground", "Ammo, money, healing, weapons and materials you can pick up.", true},
    {"EspContainers", "Loot containers", "Chests, shelves and breakable crates."},
    {"EspSavePoints", "Save points", "Where you can save."},
};

const ValueInfo kValues[ValueCount] = {
    {"DamageMult", 1, 1, 50}, {"SpeedMult", 1, 0.5f, 5}, {"JumpMult", 1, 1, 10},
    {"TimeScale", 1, 0.1f, 4}, {"Fov", 0, 0, 130},       {"KillRadius", 20, 5, 100},
    {"EspRange", 80, 10, 300}, {"EspWorldRange", 30, 5, 150},
};

const char* const kPowerNames[PowerCount] = {"Telekinesis", "Pyrokinesis", "Hellchains"};

std::atomic<bool> g_on[ToggleCount];
std::atomic<float> g_value[ValueCount];

namespace {

// The game's gameplay tags for each power (native tags, spelled as in the exe).
const char* const kPowerTags[PowerCount] = {"Character.Ability.Genesisconfiguration.Telekinesis",
                                            "Character.Ability.Genesisconfiguration.Pyrokinesis",
                                            "Character.Ability.Genesisconfiguration.Hellchains"};

using Vec = Vec3;
struct Rot {
    double pitch, yaw, roll;
};
template <class T> struct TArray {
    T* data;
    int32_t num, max;
};

constexpr uint8_t MOVE_Falling = 3, MOVE_Flying = 5;
constexpr uint8_t SlateHidden = 2, SlateCollapsed = 1;

std::mutex g_snapMutex;
Snapshot g_snap;

// Game-thread state.
struct State {
    Weak pc, player, attrs, cmc, cheat, objectives;
    Weak cheatPawn; // the pawn the tag-based cheats (invisible, infinite ammo) were applied to
    uint64_t lockAt = 0;                 // when the current lockpick close-up opened (UINT64_MAX: already opened)
    uint64_t splashAt = 0, splashSince = 0; // last / first look for the startup splash screens
    bool introsDone = false;
    std::map<std::string, Weak> cdo;
    std::map<std::string, Weak> items;
    std::vector<Weak> enemies;
    uint64_t pcScanAt = 0, enemiesAt = 0, slowAt = 0, cheatClassAt = 0;
    bool cheatTried = false, cheatClass = false;
    bool cheatState[ToggleCount] = {};
    bool applied[ToggleCount] = {};
    float lastValue[ValueCount] = {};
    std::map<std::string, float> originals; // data-asset values we changed, restored when turned off
    std::map<UObject*, int> maxAmmo, maxDurability;
    std::vector<std::pair<Weak, uint8_t>> hiddenWidgets;
    std::map<UObject*, std::pair<int32_t, float>> enemyHealth; // object index + last health seen, to measure damage
    Weak camera;                            // free camera actor
    Vec camPos{};
    uint64_t camAt = 0;
    float jumpZ = 0;
    float speedBase = -1;
    std::array<Vec, 3> slotPos{};
    std::array<std::string, 3> slotMap;
} s;

constexpr double kDegToRad = 3.14159265358979 / 180.0;
// "No cooldown" uses a tiny duration: with 0 the game's timer never fires and the action stays blocked.
constexpr float kInstant = 0.05f;
constexpr uint8_t MOVE_Walking = 1;

struct Transform { // FTransform with double precision (UE5): rotation quat, translation, scale
    double rot[4] = {0, 0, 0, 1};
    Vec pos{};
    double pad0 = 0;
    Vec scale{1, 1, 1};
    double pad1 = 0;
};
static_assert(sizeof(Transform) == 0x60);

UObject* Ptr(UObject* o, const char* prop)
{
    auto p = o ? Member<UObject*>(o, prop) : nullptr;
    return p ? *p : nullptr;
}

UObject* Cdo(const char* className)
{
    Weak& w = s.cdo[className];
    if (!w.Get()) w = Weak(FindObject(("Default__" + std::string(className)).c_str()));
    return w.Get();
}

// FGameplayAttributeData: BaseValue / CurrentValue.
struct Attr {
    float* base = nullptr;
    float* cur = nullptr;
    explicit operator bool() const { return cur != nullptr; }
    float Get() const { return cur ? *cur : 0.f; }
    void Set(float v) const
    {
        if (cur) *base = *cur = v;
    }
    // Multipliers only touch the current value: the base (what a save could store) stays pristine.
    void SetCurrent(float v) const
    {
        if (cur) *cur = v;
    }
};

Attr GetAttr(UObject* set, const char* name)
{
    Prop p = set ? FindProp(ClassOf(set), name) : Prop{};
    if (!p || !p.inner) return {};
    auto* type = static_cast<const UClass*>(p.inner);
    Prop b = FindProp(type, "BaseValue"), c = FindProp(type, "CurrentValue");
    if (!b || !c) return {};
    uint8_t* data = reinterpret_cast<uint8_t*>(set) + p.offset;
    return {reinterpret_cast<float*>(data + b.offset), reinterpret_cast<float*>(data + c.offset)};
}

UObject* AttributeSet(UObject* actor, const char* className)
{
    auto* list = Member<TArray<UObject*>>(Ptr(actor, "AbilitySystem"), "SpawnedAttributes");
    UClass* cls = FindClass(className);
    if (!list || !cls) return nullptr;
    for (int i = 0; i < list->num; i++)
        if (list->data[i] && IsA(list->data[i], cls)) return list->data[i];
    return nullptr;
}

Vec Location(UObject* actor)
{
    Call c(actor, "K2_GetActorLocation");
    return c.Run() ? c.Out<Vec>("ReturnValue") : Vec{};
}

bool Teleport(UObject* actor, Vec to)
{
    Call r(actor, "K2_GetActorRotation");
    r.Run();
    Call c(actor, "K2_TeleportTo");
    return c && c.Arg(0, to).Arg(1, r.Out<Rot>("ReturnValue")).Run();
}

double Distance(Vec a, Vec b) { return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z)); }

// Camera orientation: where it looks (pitch included) and its flat right vector.
Rot LookAxes(UObject* pc, Vec& forward, Vec& right)
{
    Call c(pc, "GetControlRotation");
    c.Run();
    Rot r = c.Out<Rot>("ReturnValue");
    double p = r.pitch * kDegToRad, y = r.yaw * kDegToRad;
    forward = {std::cos(p) * std::cos(y), std::cos(p) * std::sin(y), std::sin(p)};
    right = {-std::sin(y), std::cos(y), 0};
    return r;
}

// The game's own movement input, so any keyboard layout or a gamepad works: returned as forward / right amounts.
void MoveInput(UObject* player, const Vec& right, double& forwardAmount, double& rightAmount)
{
    Call c(player, "GetLastMovementInputVector");
    c.Run();
    Vec in = c.Out<Vec>("ReturnValue");
    forwardAmount = in.x * right.y - in.y * right.x; // flat forward = (right.y, -right.x)
    rightAmount = in.x * right.x + in.y * right.y;
}

// Velocity that flies where the camera looks.
Vec FlyVelocity(UObject* pc, UObject* player, float speed)
{
    Vec fwd, right;
    LookAxes(pc, fwd, right);
    double f, r;
    MoveInput(player, right, f, r);
    return {(fwd.x * f + right.x * r) * speed, (fwd.y * f + right.y * r) * speed, fwd.z * f * speed};
}

// Restores a float changed in a shared data asset (player settings) when the feature turns off.
void Override(UObject* obj, const char* prop, bool on, float value = 0)
{
    float* p = Member<float>(obj, prop);
    if (!p) return;
    auto it = s.originals.find(prop);
    if (on) {
        if (it == s.originals.end()) s.originals[prop] = *p;
        *p = value;
    } else if (it != s.originals.end()) {
        *p = it->second;
        s.originals.erase(it);
    }
}

// Returns the toggle state; runs `off` once when it goes from on to off.
bool Track(Toggle t, const std::function<void()>& off)
{
    bool on = g_on[t];
    if (s.applied[t] && !on) off();
    s.applied[t] = on;
    return on;
}

UObject* CheatManager()
{
    if (UObject* cm = s.cheat.Get()) return cm;
    UObject* pc = s.pc.Get();
    if (!pc || s.cheatTried) return nullptr;
    s.cheatTried = true; // once per controller

    UClass* base = FindClass("InfernoCheatManager");
    UObject** slot = Member<UObject*>(pc, "CheatManager");
    if (slot && *slot && IsA(*slot, base)) {
        s.cheat = Weak(*slot);
        km::Log("Cheat manager: using the controller's %s", Name(*slot).c_str());
        return *slot;
    }
    auto* cheatClass = Member<UClass*>(pc, "CheatClass");
    UClass* cls = cheatClass && *cheatClass && IsChildOf(*cheatClass, base) ? *cheatClass : FindClass("BP_InfernoCheatManager_C");
    if (!cls) {
        km::Log("Cheat manager: class not loaded, cheat-based options disabled");
        return nullptr;
    }
    Call spawn(Cdo("GameplayStatics"), "SpawnObject");
    spawn.Arg(0, cls).Arg(1, pc).Run();
    UObject* cm = spawn.Out<UObject*>("ReturnValue");
    if (cm && slot) *slot = cm; // owned by the controller: kept alive by the GC, visible to the game's cheat code
    km::Log("Cheat manager: spawned %s -> %s", Name(reinterpret_cast<UObject*>(cls)).c_str(), cm ? "OK" : "FAILED");
    s.cheat = Weak(cm);
    return cm;
}

// The cheat manager is created on first use only (it derives from the game's dev hotkey system and may touch input):
// until then, report whether it could be.
bool CheatAvailable()
{
    if (s.cheat.Get()) return true;
    if (s.cheatTried || !s.pc.Get()) return false;
    uint64_t now = GetTickCount64();
    if (!s.cheatClass && now - s.cheatClassAt > 1000) { // FindClass only caches hits: look for it once a second
        s.cheatClassAt = now;
        s.cheatClass = FindClass("BP_InfernoCheatManager_C") != nullptr;
    }
    return s.cheatClass;
}

bool CheatCall(const char* fn)
{
    Call c(CheatManager(), fn);
    bool ok = c && c.Run();
    km::Log("Cheat %s: %s", fn, ok ? "called" : "unavailable");
    return ok;
}

UObject* ItemManager()
{
    Call c(Cdo("CoreGameplayStatics"), "GetItemManager");
    return c.Arg(0, s.pc.Get()).Run() ? c.Out<UObject*>("ReturnValue") : nullptr;
}

UObject* FindItem(const std::string& name)
{
    Weak& w = s.items[name];
    if (!w.Get()) w = Weak(FindObject(name.c_str(), FindClass("Item")));
    return w.Get();
}

int ItemCount(UObject* item)
{
    Call c(ItemManager(), "GetItemCountInInventory");
    return c && c.Arg(0, s.player.Get()).Arg(1, item).Arg(2, false).Arg(3, false).Run() ? c.Out<int32_t>("ReturnValue") : -1;
}

void RefreshEnemies(uint64_t now)
{
    if (now - s.enemiesAt < 1000) return;
    s.enemiesAt = now;
    s.enemies.clear();
    ForEachInstance(FindClass("EnemyCharacter"), [](UObject* o) {
        s.enemies.emplace_back(o);
        return true;
    });
}

template <class F> void ForEachEnemy(F&& f)
{
    for (const Weak& w : s.enemies)
        if (UObject* e = w.Get()) f(e);
}

// Gameplay widgets currently on screen (taken when Hide HUD turns on; menus opened later are left alone).
void HideWidgets()
{
    Call hud(Cdo("CoreGameplayStatics"), "GetHUD");
    if (hud.Arg(0, s.pc.Get()).Run()) SetBool(hud.Out<UObject*>("ReturnValue"), "bShowHUD", false);
    ForEachInstance(FindClass("UserWidget"), [](UObject* w) {
        Call in(w, "IsInViewport");
        if (!in.Run() || !in.Out<bool>("ReturnValue")) return true;
        Call vis(w, "GetVisibility");
        vis.Run();
        uint8_t v = vis.Out<uint8_t>("ReturnValue");
        if (v == SlateHidden || v == SlateCollapsed) return true;
        Call(w, "SetVisibility").Arg(0, SlateHidden).Run();
        s.hiddenWidgets.emplace_back(Weak(w), v);
        return true;
    });
}

void ShowWidgets()
{
    Call hud(Cdo("CoreGameplayStatics"), "GetHUD");
    if (hud.Arg(0, s.pc.Get()).Run()) SetBool(hud.Out<UObject*>("ReturnValue"), "bShowHUD", true);
    for (auto& [w, v] : s.hiddenWidgets)
        if (UObject* o = w.Get()) Call(o, "SetVisibility").Arg(0, v).Run();
    s.hiddenWidgets.clear();
}

// Free camera: a camera actor we move ourselves while the player stays frozen in place.
void StartFreeCam(UObject* pc, UObject* player, uint64_t now)
{
    Transform t;
    t.pos = Location(player);
    t.pos.z += 60; // roughly eye height
    Call spawn(Cdo("GameplayStatics"), "BeginDeferredActorSpawnFromClass");
    spawn.Arg(0, pc).Arg(1, FindClass("CameraActor")).Arg(2, t).Arg(3, uint8_t(1)).Arg(4, static_cast<UObject*>(nullptr)).Arg(5, uint8_t(1));
    UObject* cam = spawn.Run() ? spawn.Out<UObject*>("ReturnValue") : nullptr;
    if (cam) {
        Call(Cdo("GameplayStatics"), "FinishSpawningActor").Arg(0, cam).Arg(1, t).Arg(2, uint8_t(1)).Run();
        Call(pc, "SetViewTargetWithBlend").Arg(0, cam).Arg(1, 0.f).Arg(2, uint8_t(0)).Arg(3, 0.f).Arg(4, false).Run();
        Call(s.cmc.Get(), "DisableMovement").Run();
    }
    km::Log("Free camera: %s", cam ? "on" : "camera actor could not be spawned");
    s.camera = Weak(cam);
    s.camPos = t.pos;
    s.camAt = now;
}

void StopFreeCam(UObject* pc, UObject* player)
{
    if (UObject* cam = s.camera.Get()) {
        Call(pc, "SetViewTargetWithBlend").Arg(0, player).Arg(1, 0.f).Arg(2, uint8_t(0)).Arg(3, 0.f).Arg(4, false).Run();
        Call(cam, "K2_DestroyActor").Run();
    }
    Call(s.cmc.Get(), "SetMovementMode").Arg(0, MOVE_Walking).Arg(1, uint8_t(0)).Run();
    s.camera = {};
}

void MoveFreeCam(UObject* pc, UObject* player, uint64_t now)
{
    UObject* cam = s.camera.Get();
    if (!cam) return;
    double dt = std::min((now - s.camAt) / 1000.0, 0.1);
    s.camAt = now;
    Vec v = FlyVelocity(pc, player, 1000.f * g_value[SpeedMult]);
    s.camPos = {s.camPos.x + v.x * dt, s.camPos.y + v.y * dt, s.camPos.z + v.z * dt};
    Vec fwd, right;
    Rot rot = LookAxes(pc, fwd, right);
    Call(cam, "K2_SetActorLocationAndRotation").Arg(0, s.camPos).Arg(1, rot).Arg(2, false).Arg(4, true).Run();
}

UObject* EnemyAttributes(UObject* enemy) { return AttributeSet(enemy, "CharacterAttributeSet"); }

bool KillEnemy(UObject* enemy, UObject* player)
{
    Call c(enemy, "KillEnemyInstantly");
    return c && c.Arg(0, false).Arg(1, player).Arg(2, false).Run();
}

// One-hit kill and damage multiplier, whatever the weapon or power: watch each enemy's health and,
// when it drops, remove (multiplier - 1) times the damage, or kill it outright through the game's own code.
void TickEnemyDamage(UObject* player, uint64_t now)
{
    bool oneHit = g_on[OneHitKill];
    float mult = g_value[DamageMult];
    if (!oneHit && mult <= 1.01f) {
        s.enemyHealth.clear();
        return;
    }
    bool first = s.enemyHealth.empty();
    RefreshEnemies(now);
    int tracked = 0;
    ForEachEnemy([&](UObject* e) {
        Attr h = GetAttr(EnemyAttributes(e), "Health");
        if (!h) return;
        tracked++;
        float cur = h.Get();
        int32_t index = Weak(e).index; // a new enemy may reuse a dead one's address
        auto it = s.enemyHealth.find(e);
        float last = it != s.enemyHealth.end() && it->second.first == index ? it->second.second : cur;
        if (cur > 0 && cur < last - 0.01f) {
            float left = oneHit ? 0 : cur - (last - cur) * (mult - 1);
            if (left <= 0) {
                bool ok = KillEnemy(e, player);
                km::Log("%s: %s %s", oneHit ? "One-hit kill" : "Damage multiplier", Name(e).c_str(), ok ? "killed" : "kill failed");
                cur = 0;
            } else {
                h.Set(left);
                cur = left;
            }
        }
        s.enemyHealth[e] = {index, cur};
    });
    if (s.enemyHealth.size() > 512) s.enemyHealth.clear(); // dead enemies pile up over a long session
    if (first && tracked) km::Log("Enemy damage tracking: %d of %zu enemies have health", tracked, s.enemies.size());
}

// ---------------------------------------------------------------- ESP (game-thread side)

std::mutex g_espMutex;
EspFrame g_esp;

// Bones worth drawing on any rig (human or not), each linked to its nearest drawn ancestor.
struct Skeleton {
    int32_t meshIndex = -1;
    std::vector<std::pair<uint64_t, int>> bones; // bone FName, parent slot (-1 = none)
    int head = -1;
};
std::map<UObject*, Skeleton> g_skeletons;

bool KeepBone(std::string n)
{
    for (char& c : n) c = char(std::tolower(uint8_t(c)));
    static const char* const keep[] = {"head", "neck", "spine", "pelvis", "hips", "clavicle", "upperarm", "lowerarm",
                                       "forearm", "hand", "thigh", "calf", "shin", "foot", "leg"};
    static const char* const drop[] = {"twist", "ik_", "_ik", "finger", "thumb", "index", "middle", "ring", "pinky",
                                       "toe", "ball", "corrective", "_end", "roll", "weapon", "attach", "socket", "jaw",
                                       "eye", "brow", "lip_", "cheek", "tongue", "hair", "cloth", "breast", "bag",
                                       "strap", "prop", "helper", "nub", "teeth", "nose", "camera", "_ear", "mouth",
                                       "vb_", "dummy", "root"};
    for (const char* d : drop)
        if (n.find(d) != std::string::npos) return false;
    for (const char* k : keep)
        if (n.find(k) != std::string::npos) return true;
    return false;
}

Skeleton& SkeletonOf(UObject* mesh)
{
    if (g_skeletons.size() > 256) g_skeletons.clear(); // meshes of dead enemies
    Skeleton& sk = g_skeletons[mesh];
    int32_t index = Weak(mesh).index;
    if (sk.meshIndex == index) return sk;
    sk = {};
    sk.meshIndex = index;
    Call num(mesh, "GetNumBones");
    int n = num.Run() ? std::min(num.Out<int32_t>("ReturnValue"), 512) : 0;
    std::map<uint64_t, int> slot;
    Call boneName(mesh, "GetBoneName");
    for (int i = 0; i < n; i++) {
        boneName.Arg(0, i).Run();
        uint64_t name = boneName.Out<uint64_t>("ReturnValue");
        if (!KeepBone(NameToString(&name)) || slot.count(name)) continue;
        slot[name] = int(sk.bones.size());
        if (sk.head < 0 && NameToString(&name).find("ead") != std::string::npos) sk.head = int(sk.bones.size());
        sk.bones.push_back({name, -1});
    }
    Call parentOf(mesh, "GetParentBone");
    for (auto& [name, parent] : sk.bones) {
        uint64_t cur = name;
        for (int guard = 0; guard < 64 && cur; guard++) { // FName "None" = 0
            parentOf.Arg(0, cur).Run();
            cur = parentOf.Out<uint64_t>("ReturnValue");
            if (auto it = slot.find(cur); it != slot.end()) {
                parent = it->second;
                break;
            }
        }
    }
    static int logged;
    if (logged++ < 8) km::Log("ESP skeleton: %s keeps %zu of %d bones", Name(reinterpret_cast<UObject*>(ClassOf(OuterOf(mesh)))).c_str(), sk.bones.size(), n);
    return sk;
}

// "BP_Cultist_Melee_C" -> "Cultist Melee"
std::string PrettyClass(UObject* actor)
{
    static std::map<UClass*, std::string> cache;
    UClass* cls = ClassOf(actor);
    if (auto it = cache.find(cls); it != cache.end()) return it->second;
    std::string n = Name(reinterpret_cast<UObject*>(cls));
    for (const char* prefix : {"BP_", "ABP_", "CH_", "B_"})
        if (n.rfind(prefix, 0) == 0) n.erase(0, strlen(prefix));
    if (n.size() > 2 && n.compare(n.size() - 2, 2, "_C") == 0) n.resize(n.size() - 2);
    for (const char* word : {"Character", "Base"})
        if (auto p = n.find(word); p != std::string::npos && n.size() > strlen(word)) n.erase(p, strlen(word));
    std::string out;
    for (size_t i = 0; i < n.size(); i++) {
        char c = n[i] == '_' ? ' ' : n[i];
        if (i && std::isupper(uint8_t(c)) && std::islower(uint8_t(n[i - 1]))) out += ' ';
        if (!(c == ' ' && (out.empty() || out.back() == ' '))) out += c;
    }
    while (!out.empty() && out.back() == ' ') out.pop_back();
    return cache[cls] = out.empty() ? "Enemy" : out;
}

std::vector<EspThing> g_world; // items / containers / save points with their (static) positions
uint64_t g_worldAt = 0;

void RefreshWorld(uint64_t now)
{
    if (now - g_worldAt < 1000) return;
    g_worldAt = now;
    g_world.clear();
    UClass* pickable = g_on[EspItems] ? FindClass("CorePickable") : nullptr;
    UClass* shelf = g_on[EspContainers] ? FindClass("ShelfLootContainer") : nullptr;
    UClass* chest = g_on[EspContainers] ? FindClass("BP_LootContainerChest_C") : nullptr;
    UClass* crate = g_on[EspContainers] ? FindClass("BPD_DestructableLoot_C") : nullptr;
    UClass* save = g_on[EspSavePoints] ? FindClass("BP_TASK_SavePoint_C") : nullptr;
    std::vector<std::pair<UObject*, EspThing>> found;
    ForEachObject([&](UObject* o) { // one pass for every kind
        if (IsDefaultObject(o)) return true;
        EspThing t;
        if (pickable && IsA(o, pickable)) {
            bool active = true, hidden = false;
            GetBool(o, "bItemIsActive", &active);
            GetBool(o, "bHidden", &hidden);
            UObject* item = Ptr(o, "Item");
            if (!active || hidden || !item) return true;
            t.label = Name(item);
            int* stack = Member<int32_t>(o, "StackableCount");
            if (stack && *stack > 1) t.label += "  x" + std::to_string(*stack);
        } else if ((shelf && IsA(o, shelf)) || (chest && IsA(o, chest)) || (crate && IsA(o, crate))) {
            t.kind = EspKind::Container;
            t.label = IsA(o, chest) ? "Chest" : IsA(o, shelf) ? "Shelf" : "Crate";
        } else if (save && IsA(o, save)) {
            t.kind = EspKind::SavePoint;
            t.label = "Save point";
        } else {
            return true;
        }
        found.push_back({o, std::move(t)});
        return true;
    });
    for (auto& [o, t] : found) {
        t.pos = Location(o);
        g_world.push_back(std::move(t));
    }
}

void TickEsp(UObject* pc, UObject* player, uint64_t now)
{
    EspFrame f;
    f.active = g_on[Esp];
    if (f.active) {
        // Live camera: PlayerCameraManager.CameraCachePrivate.POV.{Location, Rotation, FOV}
        UObject* pcm = Ptr(pc, "PlayerCameraManager");
        Prop cache = pcm ? FindProp(ClassOf(pcm), "CameraCachePrivate") : Prop{};
        Prop pov = cache.inner ? FindProp(static_cast<const UClass*>(cache.inner), "POV") : Prop{};
        auto* view = static_cast<const UClass*>(pov.inner);
        Prop loc = view ? FindProp(view, "Location") : Prop{}, rot = view ? FindProp(view, "Rotation") : Prop{},
             fov = view ? FindProp(view, "FOV") : Prop{};
        if (loc && rot && fov) {
            uintptr_t base = reinterpret_cast<uintptr_t>(pcm) + cache.offset + pov.offset;
            f.povLocation = base + loc.offset;
            f.povRotation = base + rot.offset;
            f.povFov = base + fov.offset;
        }

        Vec me = Location(player);
        double range = g_value[EspRange] * 100.0, worldRange = g_value[EspWorldRange] * 100.0;
        bool bones = g_on[EspSkeleton] || g_on[EspChams] || g_on[EspHead];
        RefreshEnemies(now);
        ForEachEnemy([&](UObject* e) {
            Attr h = GetAttr(EnemyAttributes(e), "Health"), m = GetAttr(EnemyAttributes(e), "MaxHealth");
            if (h && h.Get() <= 0) return; // dead
            Vec p = Location(e);
            double d = Distance(me, p);
            if (d > range) return;
            float* half = Member<float>(Ptr(e, "CapsuleComponent"), "CapsuleHalfHeight");
            float hh = half ? *half : 90.f;
            EspEnemy en;
            en.name = PrettyClass(e);
            en.feet = {p.x, p.y, p.z - hh};
            en.top = {p.x, p.y, p.z + hh};
            en.health = h.Get();
            en.maxHealth = m.Get();
            en.distance = float(d / 100.0);
            UObject* mesh = Ptr(e, "Mesh");
            if (bones && mesh && f.enemies.size() < 24) {
                Skeleton& sk = SkeletonOf(mesh);
                std::vector<Vec> pos(sk.bones.size());
                Call socket(mesh, "GetSocketLocation");
                for (size_t i = 0; i < sk.bones.size(); i++) pos[i] = socket.Arg(0, sk.bones[i].first).Run() ? socket.Out<Vec>("ReturnValue") : Vec{};
                for (size_t i = 0; i < sk.bones.size(); i++)
                    if (sk.bones[i].second >= 0) en.bones.push_back({pos[i], pos[size_t(sk.bones[i].second)]});
                if (sk.head >= 0) {
                    en.head = pos[size_t(sk.head)];
                    en.hasHead = true;
                }
            }
            f.enemies.push_back(std::move(en));
        });

        if (g_on[EspItems] || g_on[EspContainers] || g_on[EspSavePoints]) {
            RefreshWorld(now);
            for (const EspThing& t : g_world) {
                double d = Distance(me, t.pos);
                if (d > worldRange) continue;
                EspThing copy = t;
                copy.distance = float(d / 100.0);
                f.things.push_back(std::move(copy));
            }
        }
    }
    std::lock_guard lock(g_espMutex);
    g_esp = std::move(f);
}

void TickPlayer(UObject* player, uint64_t now, Snapshot& snap)
{
    UObject* pc = s.pc.Get();
    UObject* attrs = s.attrs.Get();
    UObject* cmc = s.cmc.Get();
    UObject* settings = Ptr(player, "CharacterSettings");
    auto& why = snap.why;

    Attr health = GetAttr(attrs, "Health"), maxHealth = GetAttr(attrs, "MaxHealth");
    Attr suffering = GetAttr(attrs, "Suffering"), maxSuffering = GetAttr(attrs, "MaxSuffering");
    snap.health = health.Get();
    snap.maxHealth = maxHealth.Get();
    snap.suffering = suffering.Get();
    snap.maxSuffering = maxSuffering.Get();

    // Powers given so far (a tag container: its first member is the tag array), and the Genesis Configuration itself.
    auto* given = Member<TArray<uint64_t>>(player, "GivenGenesisConfigurationAbilities");
    bool hasBox = false;
    snap.powersWhy = !given || !GetBool(player, "bHasGenesisConfiguration", &hasBox) ? "Powers not found."
                     : !hasBox ? "Get the Genesis Configuration first: the story gives it."
                               : "";
    for (int p = 0; p < PowerCount; p++) {
        snap.powers[p] = false;
        for (int i = 0; given && i < given->num && i < 32; i++)
            snap.powers[p] = snap.powers[p] || _stricmp(NameToString(&given->data[i]).c_str(), kPowerTags[p]) == 0;
    }

    // Player
    if (!health || !maxHealth) why[GodMode] = why[InfiniteHealth] = "Health attribute not found.";
    if (Track(GodMode, [&] { SetBool(player, "bCanBeDamaged", true); })) SetBool(player, "bCanBeDamaged", false);
    if ((g_on[GodMode] || g_on[InfiniteHealth]) && health.Get() < maxHealth.Get()) health.Set(maxHealth.Get());

    if (!Member<float>(settings, "SprintCooldownAfterSprint")) why[NoSprintCooldown] = "Sprint settings not found.";
    bool sprint = g_on[NoSprintCooldown];
    Override(settings, "SprintCooldownAfterSprint", sprint, kInstant);
    Override(settings, "SprintCooldownAfterShooting", sprint, kInstant);

    if (!CheatAvailable()) why[Invisible] = "The developers' cheat manager isn't available.";
    // These cheats flip a state on each call: mirror it (reset when the cheat manager is recreated).
    // Their state is a tag on the pawn's ability system (Cheats.Character.Invisible / .infiniteAmmo), so a new pawn
    // (death, reload) starts without them; the same pawn coming back after a cutscene keeps them.
    if (s.cheatPawn.Get() != player) {
        s.cheatPawn = Weak(player);
        s.cheatState[Invisible] = s.cheatState[InfiniteAmmo] = false;
    }
    auto cheatToggle = [&](Toggle t, const char* fn) {
        if (g_on[t] != s.cheatState[t] && (g_on[t] || s.cheat.Get()) && CheatAvailable() && CheatCall(fn))
            s.cheatState[t] = g_on[t];
    };
    cheatToggle(Invisible, "K2_InvisiblePlayer");
    cheatToggle(InfiniteAmmo, "K2_ToggleUnlimitedAmmo");

    if (!FindClass("EnemyCharacter")) why[OneHitKill] = snap.valueWhy[DamageMult] = "Enemy class not found.";
    TickEnemyDamage(player, now);

    // Combat
    UObject* item = Ptr(player, "CurrentEquipmentItemInfo");
    if (g_on[InfiniteAmmo]) { // also keep the magazine full ourselves: covers the cheat being missing or removed
        int* ammo = item && IsA(item, FindClass("ItemInfoRangedWeapon")) ? Member<int>(item, "AmmoInClip") : nullptr;
        if (ammo) {
            int& top = s.maxAmmo[item];
            float* clip = Member<float>(item, "ClipSizeInfo");
            top = std::max({top, *ammo, clip ? int(*clip) : 0});
            *ammo = top;
        }
    }
    // Auto lockpick: once a lockpick close-up has been open for a moment, let the game's own puzzle skip open it.
    // The player state points at the puzzle task only while a puzzle is open, so the class lookups stay rare.
    auto flag = [](UObject* o, const char* name) {
        bool v = false;
        return GetBool(o, name, &v) && v;
    };
    UObject* task = g_on[AutoLockpick] ? Ptr(Ptr(pc, "PlayerState"), "PuzzleRef") : nullptr;
    UObject* puzzle = task && IsA(task, FindClass("BP_TASK_FocusEnvPuzzle_C")) ? Ptr(task, "PuzzleActorRef") : nullptr;
    if (!puzzle || !IsA(puzzle, FindClass("BP_EnvPuzzleBaseActor_LockpickPuzzle_C")) || !flag(puzzle, "bPuzzleActive") ||
        flag(puzzle, "PuzzleFinished")) {
        s.lockAt = 0;
    } else if (!s.lockAt) {
        s.lockAt = now;
    } else if (s.lockAt != UINT64_MAX && now - s.lockAt > 600) {
        s.lockAt = UINT64_MAX; // once per close-up
        bool ok = Call(task, "SkipPuzzle").Run() || Call(puzzle, "PuzzleSkipped").Run();
        km::Log("Auto lockpick: %s", ok ? "lock opened" : "the puzzle can't be skipped");
    }

    if (!FindProp(ClassOf(player), "bIgnoreSufferingCost")) why[NoSufferingCost] = "Suffering settings not found.";
    if (Track(NoSufferingCost, [&] {
            SetBool(player, "bIgnoreSufferingCost", false);
            SetBool(player, "bInfiniteSuffering", false);
        })) {
        SetBool(player, "bIgnoreSufferingCost", true);
        SetBool(player, "bInfiniteSuffering", true);
        if (suffering.Get() < maxSuffering.Get()) suffering.Set(maxSuffering.Get());
    }
    bool cooldown = g_on[NoPowerCooldown];
    if (!Member<float>(settings, "TelekinesisReleaseSuccessCooldown")) why[NoPowerCooldown] = "Power settings not found.";
    for (const char* p : {"TelekinesisReleaseSuccessCooldown", "TelekinesisReleaseFailCooldown",
                          "PyrokinesisFlamePillarReignitionCooldown", "PyrokinesisLabyrinthFireReignitionCooldown"})
        Override(settings, p, cooldown, kInstant);
    if (g_on[Unbreakable] && item && IsA(item, FindClass("ItemInfoMeleeWeapon"))) {
        if (int* d = Member<int>(item, "Durability")) {
            int& top = s.maxDurability[item];
            top = std::max(top, *d);
            *d = top;
        }
    }

    // Movement
    if (!cmc) why[Fly] = why[Noclip] = why[FreeCam] = "Movement component not found.";
    if (!FindClass("CameraActor")) why[FreeCam] = "Camera class not found.";
    bool camWasOn = s.applied[FreeCam];
    if (Track(FreeCam, [&] { StopFreeCam(pc, player); })) {
        if (!camWasOn) StartFreeCam(pc, player, now);
        MoveFreeCam(pc, player, now);
    }
    bool fly = (g_on[Fly] || g_on[Noclip]) && !g_on[FreeCam]; // the free camera freezes the player
    static bool flying;
    if (cmc && fly) {
        float speed = 1000.f * g_value[SpeedMult];
        SetBool(cmc, "bCheatFlying", true);
        if (auto* mode = Member<uint8_t>(cmc, "MovementMode"); mode && *mode != MOVE_Flying)
            Call(cmc, "SetMovementMode").Arg(0, MOVE_Flying).Arg(1, uint8_t(0)).Run();
        if (auto* max = Member<float>(cmc, "MaxFlySpeed")) *max = speed;
        if (auto* v = Member<Vec>(cmc, "Velocity")) *v = FlyVelocity(pc, player, speed); // where you look
    } else if (cmc && flying) {
        SetBool(cmc, "bCheatFlying", false);
        Call(cmc, "SetMovementMode").Arg(0, MOVE_Falling).Arg(1, uint8_t(0)).Run();
    }
    flying = fly && cmc;
    if (Track(Noclip, [&] { Call(player, "SetActorEnableCollision").Arg(0, true).Run(); }))
        Call(player, "SetActorEnableCollision").Arg(0, false).Run();

    Attr speedAttr = GetAttr(attrs, "SpeedMultiplier");
    float speed = g_value[SpeedMult];
    if (!speedAttr) snap.valueWhy[SpeedMult] = "Speed attribute not found.";
    else {
        if (s.speedBase < 0) s.speedBase = *speedAttr.base;
        if (speed != 1 || s.lastValue[SpeedMult] != 1) speedAttr.SetCurrent(s.speedBase * speed);
    }
    float jump = g_value[JumpMult];
    if (float* z = Member<float>(cmc, "JumpZVelocity")) {
        if (s.jumpZ <= 0) s.jumpZ = *z;
        if (jump != 1 || s.lastValue[JumpMult] != 1) *z = s.jumpZ * jump;
    } else {
        snap.valueWhy[JumpMult] = "Jump settings not found.";
    }

    // World
    if (g_on[FreezeAI] || s.applied[FreezeAI]) RefreshEnemies(now);
    auto dilate = [](float value) {
        ForEachEnemy([value](UObject* e) {
            if (float* d = Member<float>(e, "CustomTimeDilation")) *d = value;
        });
    };
    if (Track(FreezeAI, [&] { dilate(1); })) dilate(0);

    float time = g_value[TimeScale];
    static uint64_t timeAt; // a level load resets time dilation: re-apply now and then
    if (time != s.lastValue[TimeScale] || (time != 1 && now - timeAt > 2000)) {
        timeAt = now;
        Call(Cdo("GameplayStatics"), "SetGlobalTimeDilation").Arg(0, pc).Arg(1, time).Run();
    }
    float fov = g_value[Fov];
    if (fov != s.lastValue[Fov]) Call(pc, "FOV").Arg(0, fov).Run();

    bool hudWasHidden = s.applied[HideHUD];
    if (Track(HideHUD, ShowWidgets) && !hudWasHidden) HideWidgets();

    for (int v = 0; v < ValueCount; v++) s.lastValue[v] = g_value[v];
}

void SlowRefresh(UObject* player, Snapshot& snap)
{
    UObject* pc = s.pc.Get();
    snap.money = ItemCount(FindItem("Item_Currency"));
    Call shop(Cdo("ShopFunctions"), "GetShopItemAvailability");
    snap.shopLevel = shop.Arg(0, pc).Run() ? shop.Out<int32_t>("ReturnValue") : -1;
    snap.map = Name(OuterOf(OuterOf(player))); // player -> PersistentLevel -> World

    // Items, grouped by the class of their data asset.
    static const std::map<std::string, std::string> kCategory = {
        {"CurrencyItem", "Currency"},       {"AmmoItem", "Ammo"},
        {"WeaponRangedItem", "Firearms"},   {"WeaponMeleeItem", "Melee weapons"},
        {"ItemWeaponUpgrade", "Weapon upgrades"}, {"ItemEquipableToolMultiUserUsable", "Healing"},
        {"ItemEquippableTool", "Tools"},    {"ItemEquippable", "Equipment"},
    };
    std::map<std::string, std::vector<Named>> byCat;
    ForEachInstance(FindClass("Item"), [&](UObject* o) {
        auto it = kCategory.find(Name(reinterpret_cast<UObject*>(ClassOf(o))));
        byCat[it == kCategory.end() ? "Misc" : it->second].push_back({Name(o), 0});
        return true;
    });
    snap.items.clear();
    for (auto& [cat, list] : byCat) {
        std::sort(list.begin(), list.end(), [](const Named& a, const Named& b) { return a.name < b.name; });
        snap.items.emplace_back(cat, std::move(list));
    }

    // Objectives (gameplay tags) from the objective subsystem.
    if (!s.objectives.Get()) ForEachInstance(FindClass("ObjectiveSystem"), [](UObject* o) {
            s.objectives = Weak(o);
            return false;
        });
    snap.objectivesActive.clear();
    snap.objectivesDone.clear();
    snap.tracked.clear();
    if (UObject* sys = s.objectives.Get()) {
        auto tags = [&](const char* prop) {
            std::vector<uint64_t> out;
            Prop p = FindProp(ClassOf(sys), prop);
            Prop arr = p.inner ? FindProp(static_cast<const UClass*>(p.inner), "GameplayTags") : Prop{};
            if (!arr) return out;
            auto* list = reinterpret_cast<TArray<uint64_t>*>(reinterpret_cast<uint8_t*>(sys) + p.offset + arr.offset);
            out.assign(list->data, list->data + list->num);
            return out;
        };
        auto done = tags("CompletedObjectives");
        for (uint64_t t : tags("StartedObjectives"))
            if (std::find(done.begin(), done.end(), t) == done.end()) snap.objectivesActive.push_back({NameToString(&t), t});
        for (uint64_t t : done) snap.objectivesDone.push_back({NameToString(&t), t});
        if (auto* tracked = Member<uint64_t>(sys, "TrackedObjective")) snap.tracked = NameToString(tracked);
    }

    // Level checkpoints, nearest first.
    Vec me = Location(player);
    std::vector<std::pair<double, Named>> cps;
    ForEachInstance(FindClass("LevelCheckpoint"), [&](UObject* o) {
        double d = Distance(me, Location(o)) / 100.0;
        char label[96];
        snprintf(label, sizeof(label), "%s  ·  %.0f m", Name(o).c_str(), d);
        cps.push_back({d, {label, uint64_t(Weak(o).index)}});
        return true;
    });
    std::sort(cps.begin(), cps.end(), [](auto& a, auto& b) { return a.first < b.first; });
    snap.checkpoints.clear();
    for (auto& c : cps) snap.checkpoints.push_back(c.second);
}

// Startup logos and notices: as soon as the splash widget exists, mark each screen skipped and shrink its durations
// so it ends at once through its own flow. The interactive screens (EULA, brightness) are left alone.
void TickIntros(uint64_t now)
{
    if (s.introsDone || !g_on[SkipIntros] || now - s.splashAt < 100) return;
    if (!s.splashAt) s.splashSince = now;
    s.splashAt = now;
    if (now - s.splashSince > 60000) s.introsDone = true; // missed them (menu loaded late): stop scanning
    UObject* splash = nullptr; // the live widget, not a template: the one whose screens exist
    ForEachInstance(FindClass("W_SplashScreens_C"), [&](UObject* o) {
        if (Ptr(o, "W_SplashScreen_Saber")) splash = o;
        return !splash;
    });
    int changed = 0;
    for (const char* name : {"W_SplashScreen_Warning", "W_SplashScreen_UE", "W_SplashScreen_Saber", "W_SplashScreen_BTG",
                             "W_SplashScreen_Photosensitivty", "W_SplashScreen_JoyCon", "W_SplashScreen_AutoSave"}) {
        UObject* screen = Ptr(splash, name);
        if (!screen) continue;
        changed++;
        SetBool(screen, "bSkip", true);
        for (const char* d : {"StayDuration", "FadeDuration"})
            if (double* v = Member<double>(screen, d)) *v = 0.01;
    }
    if (!changed) return; // not created yet (or its screens aren't built yet)
    s.introsDone = true;
    km::Log("Intros: %d splash screens skipped", changed);
}

void Tick()
{
    uint64_t now = GetTickCount64();
    Snapshot snap;
    {
        std::lock_guard lock(g_snapMutex);
        snap = g_snap; // keep the slow-refresh lists between refreshes
    }
    snap.reflection = Ready();
    snap.why.fill("");
    snap.valueWhy.fill("");

    if (!s.pc.Get() && now - s.pcScanAt > 1000) {
        s.pcScanAt = now;
        UObject* pc = nullptr;
        ForEachInstance(FindClass("CoreController"), [&](UObject* o) {
            pc = o;
            return false;
        });
        s.pc = Weak(pc);
        s.cheat = {};
        s.cheatTried = s.cheatClass = false;
        std::fill(std::begin(s.cheatState), std::end(s.cheatState), false);
    }
    UObject* pawn = Ptr(s.pc.Get(), "Pawn");
    UObject* player = pawn && IsA(pawn, FindClass("PlayerCharacter")) ? pawn : nullptr;
    if (player != s.player.Get()) { // new level or first load: per-pawn state starts over
        s.player = Weak(player);
        s.attrs = Weak(AttributeSet(player, "PlayerAttributeSet"));
        s.cmc = Weak(Ptr(player, "CharacterMovement"));
        s.jumpZ = 0;
        s.speedBase = -1;
        s.maxAmmo.clear();
        s.maxDurability.clear();
        s.hiddenWidgets.clear();
        s.camera = {};
        std::fill(std::begin(s.applied), std::end(s.applied), false);
        for (int v = 0; v < ValueCount; v++) s.lastValue[v] = kValues[v].def; // re-apply values to the new pawn
        if (player) km::Log("Player found: %s", Name(player).c_str());
    }

    snap.player = player != nullptr;
    if (player) s.introsDone = true; // the intros only play before the first save is loaded
    TickIntros(now);
    if (player) {
        TickPlayer(player, now, snap);
        TickEsp(s.pc.Get(), player, now);
        if (now - s.slowAt > 1500) {
            s.slowAt = now;
            SlowRefresh(player, snap);
        }
    } else {
        snap.why.fill("Load a save first.");
        snap.why[SkipIntros].clear(); // works from the title screen
        snap.valueWhy.fill("Load a save first.");
        snap.powersWhy = "Load a save first.";
        snap.powers = {};
        snap.money = snap.shopLevel = -1;
        std::lock_guard lock(g_espMutex);
        g_esp = {};
    }
    if (!snap.reflection) snap.why.fill("Game engine not hooked: see KetamineMenu.log.");
    snap.cheatManager = CheatAvailable();
    for (int i = 0; i < 3; i++) snap.slots[i] = s.slotMap[i];

    std::lock_guard lock(g_snapMutex);
    g_snap = std::move(snap);
}

template <class F> void OnGame(F&& f)
{
    RunOnGameThread([f = std::forward<F>(f)] {
        if (UObject* player = s.player.Get()) f(player);
    });
}

} // namespace

EspFrame GetEspFrame()
{
    std::lock_guard lock(g_espMutex);
    return g_esp;
}

Snapshot GetSnapshot()
{
    Snapshot snap;
    {
        std::lock_guard lock(g_snapMutex);
        snap = g_snap;
    }
    if (!Ready() && GetEnvironmentVariableA("KM_PREVIEW", nullptr, 0)) { // test host: sample values for screenshots
        snap.reflection = snap.player = snap.cheatManager = true;
        snap.health = 74, snap.maxHealth = 100, snap.suffering = 45, snap.maxSuffering = 100;
        snap.money = 1040, snap.shopLevel = 2;
        snap.map = snap.slots[0] = "MAP_EP_5";
        snap.powers = {true, false, false};
        snap.powersWhy.clear();
        return snap;
    }
    // The tick never runs without the engine hooks: grey everything out here.
    if (!Ready()) {
        snap.reflection = false;
        snap.why.fill("Game engine not hooked: see KetamineMenu.log.");
        snap.valueWhy.fill("Game engine not hooked: see KetamineMenu.log.");
        snap.powersWhy = "Game engine not hooked: see KetamineMenu.log.";
    }
    return snap;
}

void Init()
{
    for (int t = 0; t < ToggleCount; t++) g_on[t] = cfg::GetInt("Toggles", kToggles[t].key, kToggles[t].def) != 0;
    for (int v = 0; v < ValueCount; v++) {
        g_value[v] = std::clamp(cfg::GetFloat("Values", kValues[v].key, kValues[v].def), kValues[v].min, kValues[v].max);
        if (kValues[v].key == std::string("Fov") && g_value[v] < 30) g_value[v] = 0; // 0 = game default
        s.lastValue[v] = kValues[v].def;
    }
    for (int i = 0; i < 3; i++) {
        std::string slot = cfg::GetString("Teleport", ("Slot" + std::to_string(i + 1)).c_str());
        char map[128] = {};
        Vec p{};
        if (sscanf_s(slot.c_str(), "%127[^,],%lf,%lf,%lf", map, unsigned(sizeof(map)), &p.x, &p.y, &p.z) == 4) {
            s.slotMap[i] = map;
            s.slotPos[i] = p;
        }
    }
    SetTick(Tick);
}

void Save()
{
    for (int t = 0; t < ToggleCount; t++) cfg::SetInt("Toggles", kToggles[t].key, g_on[t] ? 1 : 0);
    for (int v = 0; v < ValueCount; v++) cfg::SetFloat("Values", kValues[v].key, g_value[v]);
}

void SetHealth(float value)
{
    OnGame([value](UObject*) {
        Attr h = GetAttr(s.attrs.Get(), "Health"), m = GetAttr(s.attrs.Get(), "MaxHealth");
        if (h && m) h.Set(std::clamp(value, 1.f, m.Get()));
    });
}

void Heal()
{
    OnGame([](UObject*) {
        Attr h = GetAttr(s.attrs.Get(), "Health"), m = GetAttr(s.attrs.Get(), "MaxHealth");
        if (h && m) h.Set(m.Get());
    });
}

void FillSuffering()
{
    OnGame([](UObject*) {
        Attr h = GetAttr(s.attrs.Get(), "Suffering"), m = GetAttr(s.attrs.Get(), "MaxSuffering");
        if (h && m) h.Set(m.Get());
    });
}

void GiveItem(const std::string& name, int count)
{
    OnGame([name, count](UObject* player) {
        UObject* item = FindItem(name);
        if (!item || count <= 0) return;
        int before = ItemCount(item);
        Call cheat(CheatManager(), "K2_GiveItem");
        if (cheat) cheat.Arg(0, item).Arg(1, count).Run();
        int after = ItemCount(item);
        if (cheat && after > before) {
            km::Log("Give %s x%d: OK via cheat manager (%d -> %d)", name.c_str(), count, before, after);
            menu::Toast("+" + std::to_string(after - before) + "  " + Pretty(name));
            return;
        }
        // Fallback: the game's own inventory code.
        UObject* im = ItemManager();
        UClass* stackable = FindClass("ItemInfoStackable");
        for (int i = 0, left = count; left > 0 && i < 50; i++) {
            Call create(im, "CreateAndInitializeItem");
            if (!create.Arg(0, item).Arg(1, player).Run()) break;
            UObject* info = create.Out<UObject*>("ItemInfoRef");
            if (!info) break;
            int n = 1;
            if (IsA(info, stackable)) {
                n = left;
                *Member<int32_t>(info, "StackableCount") = n;
            }
            Call(im, "AddItemInInventory").Arg(0, info).Arg(1, player).Arg(2, false).Arg(3, false).Arg(4, false).Run();
            left -= n;
        }
        int after2 = ItemCount(item);
        km::Log("Give %s x%d: %s via item manager (%d -> %d)", name.c_str(), count, after2 > before ? "OK" : "FAILED",
                before, after2);
        char failed[160];
        snprintf(failed, sizeof(failed), lang::T("Couldn't give %s"), Pretty(name).c_str());
        menu::Toast(after2 > before ? "+" + std::to_string(after2 - before) + "  " + Pretty(name) : failed);
    });
}

void AddMoney(int delta)
{
    if (delta > 0) return GiveItem("Item_Currency", delta);
    OnGame([delta](UObject* player) {
        UObject* currency = FindItem("Item_Currency");
        UObject* im = ItemManager();
        int left = -delta;
        for (int i = 0; left > 0 && i < 50; i++) { // money may sit in several stacks
            Call get(im, "GetItemFromInventory");
            if (!get.Arg(0, player).Arg(1, currency).Arg(2, false).Run()) break;
            UObject* info = get.Out<UObject*>("ReturnValue");
            int* stack = Member<int32_t>(info, "StackableCount");
            if (!stack || *stack <= 0) break;
            int n = std::min(left, *stack);
            Call(im, "RemoveItem").Arg(0, info).Arg(1, n).Arg(2, false).Run();
            left -= n;
        }
        km::Log("Remove money %d: %d left to remove", -delta, left);
    });
}

void GiveAllSkins()
{
    OnGame([](UObject*) {
        menu::Toast(lang::T(CheatCall("K2_AddAllSkinsAndCharms") ? "Skins & charms unlocked" : "Skins & charms: cheat unavailable"));
    });
}

void SetShopLevel(int level)
{
    OnGame([level](UObject*) {
        Call(Cdo("ShopFunctions"), "SetShopItemAvailability").Arg(0, s.pc.Get()).Arg(1, level).Arg(2, false).Run();
    });
}

void KillNearby()
{
    OnGame([](UObject* player) {
        s.enemiesAt = 0;
        RefreshEnemies(GetTickCount64());
        Vec me = Location(player);
        double radius = g_value[KillRadius] * 100.0;
        int killed = 0;
        ForEachEnemy([&](UObject* e) {
            if (Distance(me, Location(e)) > radius) return;
            Call c(e, "KillEnemyInstantly");
            if (c && c.Arg(0, false).Arg(1, player).Arg(2, false).Run()) killed++;
        });
        km::Log("Kill nearby: %d enemies within %.0f m", killed, radius / 100);
        char text[96];
        snprintf(text, sizeof(text), lang::T(killed == 1 ? "%d enemy killed" : "%d enemies killed"), killed);
        menu::Toast(text);
    });
}

void SaveSlot(int slot)
{
    OnGame([slot](UObject* player) {
        s.slotPos[slot] = Location(player);
        s.slotMap[slot] = Name(OuterOf(OuterOf(player)));
        char buf[192];
        snprintf(buf, sizeof(buf), "%s,%.1f,%.1f,%.1f", s.slotMap[slot].c_str(), s.slotPos[slot].x, s.slotPos[slot].y,
                 s.slotPos[slot].z);
        cfg::SetString("Teleport", ("Slot" + std::to_string(slot + 1)).c_str(), buf);
    });
}

void LoadSlot(int slot)
{
    OnGame([slot](UObject* player) {
        if (s.slotMap[slot] == Name(OuterOf(OuterOf(player)))) Teleport(player, s.slotPos[slot]);
    });
}

void TeleportCheckpoint(uint64_t index)
{
    OnGame([index](UObject* player) {
        UObject* cp = ObjectAt(int32_t(index));
        if (cp && IsA(cp, FindClass("LevelCheckpoint"))) Teleport(player, Location(cp));
    });
}

void CompleteObjective(uint64_t fname)
{
    OnGame([fname](UObject*) {
        Call c(Cdo("ObjectiveFunctions"), "CompleteObjective");
        bool ok = c.Arg(0, s.pc.Get()).Arg(1, fname).Arg(2, true).Arg(3, 3.f).Run() && c.Out<bool>("ReturnValue");
        km::Log("Complete objective %s: %s", NameToString(&fname).c_str(), ok ? "OK" : "refused by the game");
    });
}

void UnlockPower(Power power)
{
    OnGame([power](UObject* player) {
        // A gameplay tag is just its FName: let the engine turn the tag's text into one.
        std::wstring text(kPowerTags[power], kPowerTags[power] + strlen(kPowerTags[power]));
        FString str{text.data(), int32_t(text.size() + 1), int32_t(text.size() + 1)};
        Call name(Cdo("KismetStringLibrary"), "Conv_StringToName");
        uint64_t tag = name.Arg(0, str).Run() ? name.Out<uint64_t>("ReturnValue") : 0;
        bool ok = tag && Call(player, "AddGenesisConfigurationAbility").Arg(0, tag).Run();
        km::Log("Unlock %s (%s): %s", kPowerNames[power], tag ? NameToString(&tag).c_str() : "no tag", ok ? "called" : "failed");
    });
}

} // namespace feat
