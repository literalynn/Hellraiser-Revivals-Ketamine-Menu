<p align="center">
  <img src="docs/banner.png" alt="Hellraiser Revival's Ketamine Menu" width="100%">
</p>

<p align="center">
  <a href="README.md">English</a> ·
  <b>简体中文</b> ·
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
  一款简洁的 <b>Clive Barker's Hellraiser: Revival</b>（PC）游戏内修改器。<br>
  把一个文件放进游戏目录，按 <kbd>Insert</kbd> 或 <kbd>F8</kbd>，就这么简单。
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
  <a href="#安装">安装</a> ·
  <a href="#功能">功能</a> ·
  <a href="#使用菜单">使用</a> ·
  <a href="#常见问题--故障排除">常见问题</a> ·
  <a href="#卸载">卸载</a> ·
  <a href="#从源码构建">构建</a>
</p>

---

> [!TIP]
> 开始之前请先**备份存档**：`%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`。

## 安装

只需要一个文件，电脑上不用安装任何东西（不需要 Visual C++ 运行库，也不需要启动器）。

1. 从 [Releases 页面](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest)**下载**最新的 `KetamineMenu-vX.Y.Z.zip` 并解压。
2. **打开游戏目录**：在 Steam 中右键 *Clive Barker's Hellraiser: Revival* → **管理**（Manage）→ **浏览本地文件**（Browse local files）。
   然后依次打开 `Hellraiser` → `Binaries` → `Win64`（也就是包含 `Hellraiser-Win64-Shipping.exe` 的文件夹）。
3. **把 `winmm.dll` 复制到这个 `Win64` 文件夹。** 也可以顺便复制 `KetamineMenu.ini`（默认设置）。
4. **启动游戏**，读取存档，然后按 <kbd>Insert</kbd> 或 <kbd>F8</kbd>。

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← 可选，没有的话会自动创建
```

**Vortex：** 在 [Nexus Mods 页面](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27)点击 *Mod Manager Download* 获取。

**手动“解压到游戏目录”：** 请改用 `KetamineMenu-vX.Y.Z-Nexus.zip`。它已经包含 `Hellraiser\Binaries\Win64\` 文件夹结构，
所以 Vortex 会把它装到正确的位置，你也可以直接把它解压到游戏目录。

**Linux / Steam Deck（Proton）：** Proton 默认加载它自带的 `winmm.dll`，而不是本菜单的。在 Steam 中右键游戏 → **属性**（Properties）→ **启动选项**（Launch Options），添加 `WINEDLLOVERRIDES="winmm=n,b" %command%`。

> [!TIP]
> 如果按 <kbd>Insert</kbd> / <kbd>F8</kbd> 没有反应，请打开 DLL 旁边的 `KetamineMenu.log`：里面写清楚了找到了什么、没找到什么。
> 参见[常见问题](#常见问题--故障排除)。

## 功能

每个选项都在**运行时按名称**查找游戏数据。如果游戏更新删掉了某样东西，对应的选项会变灰，并在提示里说明原因，而不会让游戏崩溃。

<table>
<tr>
<td width="50%" valign="top">

**玩家**
- 无敌模式、无限生命
- 生命值滑块（可设为任意数值）
- 冲刺无冷却 *（游戏本身没有耐力值）*
- 敌人看不见你
- 一击必杀、伤害倍率

**战斗**
- 无限弹药
- 近战武器永不损坏
- 创世构型（Genesis Configuration）能力不消耗痛苦值
- 能力无冷却、填满痛苦值
- 提前解锁念动力、念火和地狱锁链（不用等剧情）
- 静默自瞄：子弹命中准星附近圆圈内最近敌人的头部（圆圈大小可调）

**移动**
- 飞行和穿墙，朝视线方向移动，使用常用的移动键或手柄
- 自由视角（角色留在原地）
- 移动速度和跳跃高度倍率
- 3 个位置存档点 + 传送到关卡内任意检查点

</td>
<td width="50%" valign="top">

**透视（ESP）**
- 敌人：方框、血条、名字、距离、骨骼、头部标记、人物高亮、射线、屏幕外箭头
- 世界：地上的物品、战利品箱、存档点
- 敌人和物品可分别设置显示距离

**物品**
- 增加或减少金钱
- 获取任意物品：弹药、武器、升级、治疗品、材料（列表直接从游戏中读取）
- 解锁武器皮肤和挂饰

**世界**
- 时间流速（慢动作 / 快进）
- 冻结敌人、击杀附近敌人
- 视野（FOV）调节（50° 到 130°，实时生效）、隐藏界面
- 自动开锁：锁会自己打开
- 跳过启动时的标志和提示（节省约 30 秒）

**进度**
- 查看进行中和已完成的任务，完成任务，修改商店等级

</td>
</tr>
</table>

### 截图

<table>
<tr>
<td><img src="docs/menu-player.png" alt="玩家"></td>
<td><img src="docs/menu-combat.png" alt="战斗"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="移动"></td>
<td><img src="docs/menu-esp.png" alt="透视"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="世界"></td>
<td><img src="docs/menu-settings.png" alt="设置"></td>
</tr>
</table>

## 使用菜单

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | 打开 / 关闭菜单（两个键都可以在 **设置** 里更改）。菜单打开时，鼠标用来操作菜单，游戏不会接收你的输入。 |
| 快捷键 | 每个开关都可以在 **设置 → 快捷键** 里绑定一个按键。快捷键在菜单关闭时也能用，并会弹出一个小提示。 |
| 悬停 | 把鼠标停在任意选项上，可以看到它的作用，或者它为什么不可用。 |
| 语言 | English、简体中文、日本語、한국어、Русский、Deutsch、Français、Español、Português (Brasil)：默认跟随 Windows 的显示语言，可在 **设置 → 语言** 中更改。 |
| 界面缩放 | 根据屏幕分辨率自动调整；可在 **设置** 里用 − / + 按钮微调。 |
| 底栏 | 菜单底部显示游戏版本、CPU、GPU、内存、分辨率和 FPS。 |
| 配置文件 | 所有设置都保存在 DLL 旁边的 `KetamineMenu.ini` 里。**设置 → 重置配置** 可以恢复默认值。 |

> [!WARNING]
> 获取关键物品或直接完成任务可能会破坏剧情流程。**请先存档。**

## 兼容性

- **游戏：** 已在 `1.1.1.227384`（Steam，2026 年 10 月更新）和 `1.0.1.227219` 上测试。其他版本也可能可用：找不到的功能会变灰。
- **渲染：** DirectX 12（默认）和 DirectX 11。
- **其他 Mod：** 本菜单使用 `winmm.dll`，不会和 ReShade（`dxgi.dll`）或 UE4SS（`dwmapi.dll`）冲突。
- **帧生成**（DLSS-G、FSR、XeSS FG）：支持，但如果菜单闪烁，请关闭帧生成。

## 常见问题 / 故障排除

<details>
<summary><b>按 Insert / F8 没有反应</b></summary>

- 确认 `winmm.dll` 放在 `Hellraiser\Binaries\Win64`（和 `Hellraiser-Win64-Shipping.exe` 在一起），而不是游戏的根目录。
- 打开同一文件夹里的 `KetamineMenu.log`。如果这个文件不存在，说明 DLL 没有被加载：请再检查一遍文件夹，以及你的杀毒软件。
- 如果你改过菜单按键，菜单底栏（以及 `KetamineMenu.ini` 里的 `[Menu] Key=` / `Key2=`）会显示当前的按键。
</details>

<details>
<summary><b>所有选项都是灰色的</b></summary>

请先读取存档：大多数选项需要玩家角色已经存在。如果标题栏显示 *引擎未连接*，说明游戏版本的变化超出了菜单目前能处理的范围。
请提交一个 issue 并附上 `KetamineMenu.log`。
</details>

<details>
<summary><b>杀毒软件报毒</b></summary>

修改器需要挂钩游戏的渲染和内存，杀毒软件的启发式检测不喜欢这种行为。这是误报：源代码就在这里，每个版本都由
[GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions) 从源代码构建。你也可以[自己构建](#从源码构建)。
</details>

<details>
<summary><b>游戏更新后有功能失效了</b></summary>

找不到的选项会变灰并显示原因。请提交一个 issue，附上你的 `KetamineMenu.log` 和游戏版本（游戏目录里的 `Version.txt`）。
</details>

<details>
<summary><b>怎么报告 bug？</b></summary>

[提交一个 issue](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues)，写明你做了什么、发生了什么，并附上最近一次游戏的
`KetamineMenu.log` 文件（每次启动游戏都会覆盖）。
</details>

## 卸载

从 `Hellraiser\Binaries\Win64` 删除 `winmm.dll`、`KetamineMenu.ini`、`KetamineMenu.log`（如果用的是 Nexus 压缩包，还有 `KetamineMenu-LICENSE.txt`）。
使用 Vortex 的话，移除这个 Mod，然后删除它留下的 `.ini` 和 `.log`。本菜单从不修改任何游戏文件。

## 从源码构建

需要：Windows，Visual Studio 2022 或更高版本（含 *使用 C++ 的桌面开发* 工作负载），CMake 3.25+。

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

生成的 DLL 是 `build\Release\winmm.dll`。Dear ImGui 和 MinHook 由 CMake 按固定版本下载并校验。
推送一个 `v*` 标签会自动构建发布用的压缩包。

<details>
<summary><b>工作原理</b></summary>

- **加载：** 游戏会导入 `winmm.dll`，所以 Windows 会优先加载游戏目录里的这个文件。所有 `winmm` 函数都会转发给系统原本的 DLL，
  然后菜单在自己的线程里启动。
- **界面：** 用 [MinHook](https://github.com/TsudaKageyu/minhook) 挂钩 DXGI 的 `Present`（DirectX 11 和 12），用
  [Dear ImGui](https://github.com/ocornut/imgui) 绘制。菜单关闭时不绘制任何东西（提示和已开启的 ESP 除外）。
- **访问游戏：** 读取 Unreal Engine 5 自带的反射数据。只有三个引擎结构是通过特征码定位的（对象列表、名称表和 `ProcessEvent`）；
  之后所有的类、属性和函数都**按名称**查找，所以大多数游戏更新都不会让它失效。游戏函数通过挂钩 `ProcessEvent` 在游戏线程上调用。
- **安全：** 每个功能都在崩溃保护下运行，缺少什么就把对应选项变灰。
</details>

## 致谢

- [Dear ImGui](https://github.com/ocornut/imgui)（MIT）和 [MinHook](https://github.com/TsudaKageyu/minhook)（BSD-2-Clause）
- [Dumper-7](https://github.com/Encryqed/Dumper-7)，用于研究游戏的类
- [Inter](https://github.com/rsms/inter) 字体（SIL Open Font License 1.1）；中文、日文和韩文使用 Windows 自带字体

## 免责声明

Ketamine Menu 是粉丝制作的工具，与 Saber Interactive、Boss Team Games 或 Clive Barker 没有任何关联，也未获得其认可。
所有商标归其各自所有者所有。使用风险自负。

## 许可证

[MIT](LICENSE)
