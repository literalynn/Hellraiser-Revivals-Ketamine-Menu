<p align="center">
  <img src="docs/banner.png" alt="Hellraiser Revival's Ketamine Menu over the game's Lament Configuration" width="100%">
</p>

<p align="center">
  <b>English</b> ·
  <a href="README.zh-CN.md">简体中文</a> ·
  <a href="README.ja.md">日本語</a> ·
  <a href="README.ko.md">한국어</a> ·
  <a href="README.ru.md">Русский</a> ·
  <a href="README.de.md">Deutsch</a> ·
  <a href="README.fr.md">Français</a> ·
  <a href="README.es.md">Español</a> ·
  <a href="README.pt-BR.md">Português (Brasil)</a>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  A clean, in-game trainer for <b>Clive Barker's Hellraiser: Revival</b> (PC).<br>
  Drop one file in the game folder, press <kbd>Insert</kbd> or <kbd>F8</kbd>, done.
</p>

<p align="center">
  <a href="https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest"><img alt="Latest release" src="https://img.shields.io/github/v/release/literalynn/Hellraiser-Revivals-Ketamine-Menu?color=AC6EE2&label=download"></a>
  <a href="https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27"><img alt="Nexus Mods" src="https://img.shields.io/badge/Nexus%20Mods-Ketamine%20Menu-F89FCD"></a>
  <a href="https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions/workflows/build.yml"><img alt="Build" src="https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions/workflows/build.yml/badge.svg"></a>
  <img alt="Game version" src="https://img.shields.io/badge/game-1.1.1.227384-F89FCD">
  <img alt="Platform" src="https://img.shields.io/badge/platform-Windows%2010%20%2F%2011%20x64-1B1B23">
  <a href="LICENSE"><img alt="License: MIT" src="https://img.shields.io/badge/license-MIT-AC6EE2"></a>
</p>

<p align="center">
  <a href="#install">Install</a> ·
  <a href="#features">Features</a> ·
  <a href="#using-the-menu">Usage</a> ·
  <a href="#faq--troubleshooting">FAQ</a> ·
  <a href="#uninstall">Uninstall</a> ·
  <a href="#build-from-source">Build</a>
</p>

---

> [!TIP]
> **Back up your saves** before you start: `%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`.

## Install

You only need one file, and nothing to install on your PC (no Visual C++ redistributable, no launcher).

1. **Download** the latest `KetamineMenu-vX.Y.Z.zip` from the [Releases page](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest) and unzip it.
2. **Open the game folder**: in Steam, right-click *Clive Barker's Hellraiser: Revival* → **Manage** → **Browse local files**.
   Then open `Hellraiser` → `Binaries` → `Win64` (the folder that contains `Hellraiser-Win64-Shipping.exe`).
3. **Copy `winmm.dll` into that `Win64` folder.** Optionally copy `KetamineMenu.ini` too (default settings).
4. **Start the game**, load a save, and press <kbd>Insert</kbd> or <kbd>F8</kbd>.

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← optional, created automatically otherwise
```

**Vortex:** get it from the [Nexus Mods page](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27) with *Mod Manager Download*.

**Manual "extract to game folder":** use `KetamineMenu-vX.Y.Z-Nexus.zip` instead. It already contains the
`Hellraiser\Binaries\Win64\` folders, so Vortex installs it in the right place, or you can extract it straight into the game folder.

**Linux / Steam Deck (Proton):** Proton loads its own `winmm.dll` instead of the menu's. In Steam, right-click the game → **Properties** → **Launch Options** and add `WINEDLLOVERRIDES="winmm=n,b" %command%`. If you use other launch tools too (such as `~/lsfg` or `gamemoderun`), put them before `%command%`, for example `WINEDLLOVERRIDES="winmm=n,b" ~/lsfg %command%`. Don't use Decky Framegen (`~/fgmod/fgmod`) with the menu: it deletes `winmm.dll` at every launch.

> [!TIP]
> If <kbd>Insert</kbd> / <kbd>F8</kbd> do nothing, open `KetamineMenu.log` next to the DLL: it says exactly what was found and what wasn't.
> See the [FAQ](#faq--troubleshooting).

## Features

Every option resolves the game's data **by name at runtime**. If a game update removes something, that option is greyed
out with the reason in a tooltip instead of crashing.

<table>
<tr>
<td width="50%" valign="top">

**Player**
- God mode, infinite health
- Health slider (set any value)
- No sprint cooldown *(the game has no stamina)*
- Invisible to enemies
- One-hit kill, damage multiplier

**Combat**
- Infinite ammo
- Unbreakable melee weapons
- Genesis Configuration powers with no Suffering cost
- No power cooldown, refill Suffering
- Unlock Telekinesis, Pyrokinesis and Hellchains before the story does
- Silent aim: your shots hit the head of the enemy nearest the crosshair, inside an adjustable circle

**Movement**
- Fly and noclip, towards where you look, with your usual movement keys or gamepad
- Free camera (your character stays in place)
- Speed and jump height multipliers
- 3 saved positions + teleport to any level checkpoint

</td>
<td width="50%" valign="top">

**ESP**
- Enemies: box, health bar, name, distance, skeleton, head marker, chams, snaplines, off-screen arrows
- World: items on the ground, loot containers, save points
- Separate range for enemies and objects

**Inventory**
- Add or remove money
- Give any item: ammo, weapons, upgrades, healing, materials (list built from the game itself)
- Unlock weapon skins & charms

**World**
- Time scale (slow motion / fast forward)
- Freeze enemies, kill enemies nearby
- FOV editor (50° to 130°, live), hide HUD
- Auto lockpick: locks open by themselves
- Skip the logos and notices at startup (about 30 s saved)

**Progress**
- See active and completed objectives, complete one, change the shop level

</td>
</tr>
</table>

### Screenshots

<table>
<tr>
<td><img src="docs/menu-player.png" alt="Player tab"></td>
<td><img src="docs/menu-combat.png" alt="Combat tab"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="Movement tab"></td>
<td><img src="docs/menu-esp.png" alt="ESP tab"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="World tab"></td>
<td><img src="docs/menu-settings.png" alt="Settings tab"></td>
</tr>
</table>

## Using the menu

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | Open / close the menu (both rebindable in **Settings**). While it is open the mouse controls the menu and the game ignores your input. |
| Hotkeys | Any switch can get its own key in **Settings → Hotkeys**. Hotkeys work with the menu closed and show a small notification. |
| Hover | Hover any option to see what it does, or why it is unavailable. |
| Language | English, 简体中文, 日本語, 한국어, Русский, Deutsch, Français, Español, Português (Brasil): follows your Windows language, change it in **Settings**. |
| UI scale | Follows your screen resolution; adjust it with the − / + buttons in **Settings**. |
| Footer | Game version, CPU, GPU, RAM, resolution and FPS at a glance, at the bottom of the menu. |
| Settings file | Everything is saved to `KetamineMenu.ini` next to the DLL. **Settings → Reset configuration** restores the defaults. |

> [!WARNING]
> Giving key items or completing objectives can break scripted sequences. **Save your game first.**

## Compatibility

- **Game:** tested with version `1.1.1.227384` (Steam, October 2026 update) and `1.0.1.227219`. Other versions may work:
  anything that can't be found is greyed out.
- **Renderer:** DirectX 12 (the default) and DirectX 11.
- **Other mods:** the menu uses `winmm.dll`, so it doesn't collide with ReShade (`dxgi.dll`) or UE4SS (`dwmapi.dll`).
- **Frame generation** (DLSS-G, FSR, XeSS FG): supported, but if the menu flickers, turn frame generation off.

## FAQ / Troubleshooting

<details>
<summary><b>Insert / F8 do nothing</b></summary>

- Check that `winmm.dll` is in `Hellraiser\Binaries\Win64` (next to `Hellraiser-Win64-Shipping.exe`), not in the top game folder.
- Open `KetamineMenu.log` in the same folder. If it doesn't exist, the DLL wasn't loaded: check the folder again and your antivirus.
- If you rebound the menu key, the footer of the menu (and `KetamineMenu.ini`, `[Menu] Key=` / `Key2=`) shows the current ones.
</details>

<details>
<summary><b>Everything is greyed out</b></summary>

Load a save first: most options need the player to exist. If the header says *Engine not hooked*, the game version changed in a way
the menu can't handle yet. Please open an issue and attach `KetamineMenu.log`.
</details>

<details>
<summary><b>My antivirus flags the DLL</b></summary>

Trainers hook into a game's rendering and memory, which antivirus heuristics dislike. This is a false positive: the source code is
right here, and every release is built from it by [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions). You can also
[build it yourself](#build-from-source).
</details>

<details>
<summary><b>The game updated and something stopped working</b></summary>

Options that can no longer be found are greyed out with the reason. Open an issue with your `KetamineMenu.log` and the game version
(`Version.txt` in the game folder).
</details>

<details>
<summary><b>How do I report a bug?</b></summary>

[Open an issue](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues) with what you did, what happened, and the `KetamineMenu.log` file
from your last session (it is overwritten every time the game starts).
</details>

## Uninstall

Delete `winmm.dll`, `KetamineMenu.ini`, `KetamineMenu.log` (and `KetamineMenu-LICENSE.txt` if you used the Nexus zip) from
`Hellraiser\Binaries\Win64`. With Vortex, remove the mod, then delete the `.ini` and `.log` it leaves behind. No game file is ever modified.

## Build from source

Requirements: Windows, Visual Studio 2022 or later with the *Desktop development with C++* workload, CMake 3.25+.

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

The DLL is `build\Release\winmm.dll`. Dear ImGui and MinHook are downloaded by CMake at pinned versions with checksums.
Pushing a `v*` tag builds the release zip automatically.

<details>
<summary><b>How it works</b></summary>

- **Loading:** the game imports `winmm.dll`, so Windows loads ours from the game folder first. Every `winmm` function is forwarded to
  the real system DLL, then the menu starts on its own thread.
- **Overlay:** hooks DXGI `Present` (DirectX 11 and 12) with [MinHook](https://github.com/TsudaKageyu/minhook) and draws with
  [Dear ImGui](https://github.com/ocornut/imgui). Nothing is rendered while the menu is closed (except notifications and the ESP if enabled).
- **Game access:** reads Unreal Engine 5's own reflection data. Only three engine structures are located by pattern (the object
  list, the name table and `ProcessEvent`); every class, property and function is then looked up **by name**, so most game
  updates don't break it. Game functions are called on the game thread through a `ProcessEvent` hook.
- **Safety:** every feature runs behind a crash guard and degrades to a greyed-out option when something is missing.
</details>

## Credits

- [Dear ImGui](https://github.com/ocornut/imgui) (MIT) and [MinHook](https://github.com/TsudaKageyu/minhook) (BSD-2-Clause)
- [Dumper-7](https://github.com/Encryqed/Dumper-7), used to study the game's classes
- [Inter](https://github.com/rsms/inter) font (SIL Open Font License 1.1); Chinese, Japanese and Korean use the Windows fonts

## Disclaimer

Ketamine Menu is a fan-made tool. It is not affiliated with or endorsed by Saber Interactive, Boss Team Games
or Clive Barker. All trademarks belong to their respective owners. Use it at your own risk.

## License

[MIT](LICENSE)
