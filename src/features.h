#pragma once
// Game features. All game access happens on the game thread (Tick and queued actions);
// the menu reads a Snapshot / EspFrame and writes the atomics below.
#include <array>
#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

namespace feat {

enum Toggle {
    GodMode, InfiniteHealth, NoSprintCooldown, OneHitKill, Invisible,
    InfiniteAmmo, NoSufferingCost, NoPowerCooldown, Unbreakable,
    Fly, Noclip,
    FreezeAI, HideHUD, FreeCam, AutoLockpick, SkipIntros,
    Esp, EspBox, EspHealth, EspName, EspDistance, EspSkeleton, EspHead, EspChams, EspSnaplines, EspOffscreen,
    EspItems, EspContainers, EspSavePoints,
    ToggleCount
};

struct ToggleInfo {
    const char* key;   // ini key
    const char* label;
    const char* help;
    bool def = false;  // default state (ESP sub-options start on so the master switch shows something)
};
extern const ToggleInfo kToggles[ToggleCount];
extern std::atomic<bool> g_on[ToggleCount];

enum Value { DamageMult, SpeedMult, JumpMult, TimeScale, Fov, KillRadius, EspRange, EspWorldRange, ValueCount };
struct ValueInfo {
    const char* key;
    float def, min, max;
};
extern const ValueInfo kValues[ValueCount];
extern std::atomic<float> g_value[ValueCount];

// Genesis Configuration powers the story unlocks one by one.
enum Power { Telekinesis, Pyrokinesis, Hellchains, PowerCount };
extern const char* const kPowerNames[PowerCount];

struct Named {
    std::string name;
    uint64_t fname = 0; // FName (objectives) or object index (checkpoints) for the action
};

struct Snapshot {
    bool reflection = false; // engine hooked
    bool player = false;     // a save is loaded and the player exists
    bool cheatManager = false;
    std::string map;
    float health = 0, maxHealth = 0, suffering = 0, maxSuffering = 0;
    int money = -1, shopLevel = -1;
    std::array<std::string, ToggleCount> why; // non-empty = unavailable, shown as tooltip
    std::array<std::string, ValueCount> valueWhy;
    std::array<bool, PowerCount> powers{}; // unlocked
    std::string powersWhy;                 // non-empty = can't unlock now
    std::vector<std::pair<std::string, std::vector<Named>>> items; // by category
    std::vector<Named> objectivesActive, objectivesDone, checkpoints;
    std::string tracked;
    std::array<std::string, 3> slots; // "" = empty, else map name
};
Snapshot GetSnapshot();

// What the ESP draws, gathered on the game thread. The camera is read live by the renderer (pointers below)
// so the overlay follows mouse look without lag.
struct Vec3 {
    double x = 0, y = 0, z = 0;
};
struct EspEnemy {
    std::string name;
    Vec3 feet, top, head;
    bool hasHead = false;
    float health = 0, maxHealth = 0, distance = 0;
    std::vector<std::pair<Vec3, Vec3>> bones; // skeleton segments, world space
};
enum class EspKind : uint8_t { Item, Container, SavePoint };
struct EspThing {
    std::string label;
    Vec3 pos;
    float distance = 0;
    EspKind kind = EspKind::Item;
};
struct EspFrame {
    bool active = false;
    uintptr_t povLocation = 0, povRotation = 0, povFov = 0; // inside the player camera manager
    std::vector<EspEnemy> enemies;
    std::vector<EspThing> things;
};
EspFrame GetEspFrame();

void Init();  // loads toggles/values from the ini, registers the game-thread tick
void Save();  // writes toggles/values to the ini

// One-shot actions, queued to the game thread.
void Heal();
void SetHealth(float value);
void FillSuffering();
void AddMoney(int delta);
void GiveItem(const std::string& name, int count);
void GiveAllSkins();
void SetShopLevel(int level);
void KillNearby();
void SaveSlot(int slot);
void LoadSlot(int slot);
void TeleportCheckpoint(uint64_t index);
void CompleteObjective(uint64_t fname);
void UnlockPower(Power power);

} // namespace feat
