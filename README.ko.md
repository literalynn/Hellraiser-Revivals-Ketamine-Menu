<p align="center">
  <img src="docs/banner.png" alt="Hellraiser Revival's Ketamine Menu" width="100%">
</p>

<p align="center">
  <a href="README.md">English</a> ·
  <a href="README.zh-CN.md">简体中文</a> ·
  <a href="README.ja.md">日本語</a> ·
  <b>한국어</b> ·
  <a href="README.ru.md">Русский</a> ·
  <a href="README.de.md">Deutsch</a> ·
  <a href="README.fr.md">Français</a> ·
  <a href="README.es.md">Español</a> ·
  <a href="README.pt-BR.md">Português (Brasil)</a>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  <b>Clive Barker's Hellraiser: Revival</b>(PC)용 깔끔한 인게임 트레이너입니다.<br>
  게임 폴더에 파일 하나를 넣고 <kbd>Insert</kbd> 또는 <kbd>F8</kbd>을 누르면 끝.
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
  <a href="#설치">설치</a> ·
  <a href="#기능">기능</a> ·
  <a href="#메뉴-사용법">사용법</a> ·
  <a href="#faq--문제-해결">FAQ</a> ·
  <a href="#제거">제거</a> ·
  <a href="#소스에서-빌드">빌드</a>
</p>

---

> [!TIP]
> 시작하기 전에 **세이브 파일을 백업**하세요: `%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`

## 설치

파일 하나만 있으면 되고, PC에 따로 설치할 것은 없습니다(Visual C++ 재배포 패키지도, 런처도 필요 없음).

1. [Releases 페이지](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest)에서 최신 `KetamineMenu-vX.Y.Z.zip`을 **다운로드**하고 압축을 풉니다.
2. **게임 폴더를 엽니다**: Steam에서 *Clive Barker's Hellraiser: Revival*을 우클릭 → **관리**(Manage) → **로컬 파일 보기**(Browse local files).
   그다음 `Hellraiser` → `Binaries` → `Win64`(`Hellraiser-Win64-Shipping.exe`가 있는 폴더)를 엽니다.
3. **`winmm.dll`을 그 `Win64` 폴더에 복사합니다.** 원하면 `KetamineMenu.ini`(기본 설정)도 함께 복사하세요.
4. **게임을 실행**하고 세이브를 불러온 뒤 <kbd>Insert</kbd> 또는 <kbd>F8</kbd>을 누릅니다.

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← 선택 사항, 없으면 자동으로 생성됨
```

**Vortex:** [Nexus Mods 페이지](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27)에서 *Mod Manager Download*로 받으세요.

**수동으로 "게임 폴더에 압축 풀기":** 대신 `KetamineMenu-vX.Y.Z-Nexus.zip`을 사용하세요. `Hellraiser\Binaries\Win64\` 폴더 구조가
이미 들어 있어서 Vortex가 올바른 위치에 설치하며, 게임 폴더에 바로 압축을 풀어도 됩니다.

> [!TIP]
> <kbd>Insert</kbd> / <kbd>F8</kbd>을 눌러도 아무 반응이 없다면 DLL 옆에 있는 `KetamineMenu.log`를 열어 보세요. 무엇을 찾았고 무엇을 못 찾았는지 정확히 적혀 있습니다.
> [FAQ](#faq--문제-해결)도 참고하세요.

## 기능

모든 옵션은 게임 데이터를 **실행 중에 이름으로** 찾습니다. 게임 업데이트로 무언가가 사라지면 해당 옵션은 크래시 대신 비활성화(회색)되고,
그 이유가 툴팁에 표시됩니다.

<table>
<tr>
<td width="50%" valign="top">

**플레이어**
- 무적 모드, 무한 체력
- 체력 슬라이더(원하는 값으로 설정)
- 달리기 쿨다운 없음 *(이 게임에는 스태미나가 없습니다)*
- 적에게 투명
- 일격필살, 피해 배율

**전투**
- 무한 탄약
- 근접 무기 파손 없음
- 제네시스 구성(Genesis Configuration) 능력 사용 시 고통 소모 없음
- 능력 쿨다운 없음, 고통 채우기
- 염력, 발화 능력, 지옥 사슬을 스토리보다 먼저 잠금 해제

**이동**
- 비행과 벽 통과: 바라보는 방향으로, 평소의 이동 키나 게임패드로 조작
- 자유 카메라(캐릭터는 제자리에 남음)
- 이동 속도와 점프 높이 배율
- 위치 저장 3곳 + 레벨 내 아무 체크포인트로 순간이동

</td>
<td width="50%" valign="top">

**ESP**
- 적: 박스, 체력 바, 이름, 거리, 뼈대, 머리 표시, 실루엣 강조, 스냅라인, 화면 밖 화살표
- 월드: 바닥의 아이템, 전리품 상자, 세이브 포인트
- 적과 오브젝트의 표시 거리를 따로 설정

**인벤토리**
- 돈 추가 또는 제거
- 아무 아이템이나 획득: 탄약, 무기, 업그레이드, 회복 아이템, 재료(목록은 게임에서 직접 생성)
- 무기 스킨과 참 잠금 해제

**월드**
- 시간 배속(슬로 모션 / 빨리 감기)
- 적 정지, 주변 적 처치
- 시야각(FOV) 편집(50°~130°, 실시간), HUD 숨기기
- 자동 자물쇠 따기: 자물쇠가 저절로 열림
- 시작할 때 로고와 안내 화면 건너뛰기 (약 30초 절약)

**진행**
- 진행 중인 목표와 완료한 목표 확인, 목표 완료, 상점 레벨 변경

</td>
</tr>
</table>

### 스크린샷

<table>
<tr>
<td><img src="docs/menu-player.png" alt="플레이어"></td>
<td><img src="docs/menu-combat.png" alt="전투"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="이동"></td>
<td><img src="docs/menu-esp.png" alt="ESP"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="월드"></td>
<td><img src="docs/menu-settings.png" alt="설정"></td>
</tr>
</table>

## 메뉴 사용법

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | 메뉴 열기 / 닫기(두 키 모두 **설정**에서 변경 가능). 메뉴가 열려 있는 동안에는 마우스로 메뉴를 조작하며, 게임은 입력을 받지 않습니다. |
| 단축키 | 모든 스위치에 **설정 → 단축키**에서 전용 키를 지정할 수 있습니다. 단축키는 메뉴가 닫혀 있어도 작동하며 작은 알림이 표시됩니다. |
| 마우스 올리기 | 옵션 위에 마우스를 올리면 기능 설명이나 사용할 수 없는 이유가 표시됩니다. |
| 언어 | English, 简体中文, 日本語, 한국어, Русский, Deutsch, Français, Español, Português (Brasil): 처음에는 Windows 표시 언어를 따르며, **설정 → 언어**에서 바꿀 수 있습니다. |
| UI 크기 | 화면 해상도에 맞춰 자동 조정되며, **설정**의 − / + 버튼으로 조절할 수 있습니다. |
| 하단 바 | 메뉴 아래쪽에 게임 버전, CPU, GPU, RAM, 해상도, FPS를 표시합니다. |
| 설정 파일 | 모든 설정은 DLL 옆의 `KetamineMenu.ini`에 저장됩니다. **설정 → 설정 초기화**로 기본값을 복원할 수 있습니다. |

> [!WARNING]
> 핵심 아이템을 얻거나 목표를 완료하면 스크립트 진행이 깨질 수 있습니다. **먼저 저장하세요.**

## 호환성

- **게임:** `1.1.1.227384`(Steam, 2026년 10월 업데이트)와 `1.0.1.227219`에서 테스트했습니다. 다른 버전에서도 작동할 수 있으며,
  찾지 못한 기능은 비활성화됩니다.
- **렌더러:** DirectX 12(기본)와 DirectX 11.
- **다른 모드:** 이 메뉴는 `winmm.dll`을 사용하므로 ReShade(`dxgi.dll`)나 UE4SS(`dwmapi.dll`)와 충돌하지 않습니다.
- **프레임 생성**(DLSS-G, FSR, XeSS FG): 지원하지만, 메뉴가 깜빡이면 프레임 생성을 꺼 주세요.

## FAQ / 문제 해결

<details>
<summary><b>Insert / F8을 눌러도 아무 반응이 없어요</b></summary>

- `winmm.dll`이 게임 최상위 폴더가 아니라 `Hellraiser\Binaries\Win64`(`Hellraiser-Win64-Shipping.exe`와 같은 위치)에 있는지 확인하세요.
- 같은 폴더의 `KetamineMenu.log`를 여세요. 이 파일이 없다면 DLL이 로드되지 않은 것입니다: 폴더와 백신 프로그램을 다시 확인하세요.
- 메뉴 키를 바꿨다면 메뉴 하단 바(그리고 `KetamineMenu.ini`의 `[Menu] Key=` / `Key2=`)에 현재 키가 표시됩니다.
</details>

<details>
<summary><b>모든 옵션이 회색이에요</b></summary>

먼저 세이브를 불러오세요: 대부분의 옵션은 플레이어가 존재해야 합니다. 상단에 *엔진 미연결*이라고 표시되면, 게임 버전이 메뉴가 아직 처리할 수 없는
방식으로 바뀐 것입니다. issue를 열고 `KetamineMenu.log`를 첨부해 주세요.
</details>

<details>
<summary><b>백신 프로그램이 DLL을 탐지해요</b></summary>

트레이너는 게임의 렌더링과 메모리에 후킹하기 때문에 백신의 휴리스틱 탐지에 걸리기 쉽습니다. 이것은 오탐입니다: 소스 코드가 바로 여기 있고,
모든 릴리스는 [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions)에서 소스로부터 빌드됩니다.
[직접 빌드](#소스에서-빌드)할 수도 있습니다.
</details>

<details>
<summary><b>게임 업데이트 후 일부 기능이 작동하지 않아요</b></summary>

더 이상 찾을 수 없는 옵션은 이유와 함께 비활성화됩니다. `KetamineMenu.log`와 게임 버전(게임 폴더의 `Version.txt`)을 첨부해 issue를 열어 주세요.
</details>

<details>
<summary><b>버그는 어떻게 제보하나요?</b></summary>

[issue를 열고](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues) 무엇을 했는지, 무슨 일이 일어났는지 적은 다음, 마지막 플레이의
`KetamineMenu.log` 파일(게임을 실행할 때마다 덮어써짐)을 첨부해 주세요.
</details>

## 제거

`Hellraiser\Binaries\Win64`에서 `winmm.dll`, `KetamineMenu.ini`, `KetamineMenu.log`(Nexus zip을 사용했다면 `KetamineMenu-LICENSE.txt`도)를 삭제하세요.
Vortex를 사용했다면 모드를 제거한 뒤 남은 `.ini`와 `.log`를 삭제하세요. 게임 파일은 절대 수정되지 않습니다.

## 소스에서 빌드

필요한 것: Windows, Visual Studio 2022 이상(*C++를 사용한 데스크톱 개발* 워크로드), CMake 3.25 이상.

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

DLL은 `build\Release\winmm.dll`에 생성됩니다. Dear ImGui와 MinHook은 CMake가 고정된 버전으로 체크섬과 함께 다운로드합니다.
`v*` 태그를 푸시하면 릴리스 zip이 자동으로 빌드됩니다.

<details>
<summary><b>작동 원리</b></summary>

- **로딩:** 게임이 `winmm.dll`을 임포트하므로 Windows는 게임 폴더에 있는 이 파일을 먼저 불러옵니다. 모든 `winmm` 함수는 원래의 시스템 DLL로
  전달되고, 메뉴는 자체 스레드에서 시작됩니다.
- **오버레이:** [MinHook](https://github.com/TsudaKageyu/minhook)으로 DXGI `Present`(DirectX 11과 12)를 후킹하고
  [Dear ImGui](https://github.com/ocornut/imgui)로 그립니다. 메뉴가 닫혀 있으면 아무것도 그리지 않습니다(알림과 켜 둔 ESP 제외).
- **게임 접근:** Unreal Engine 5 자체의 리플렉션 데이터를 읽습니다. 패턴으로 찾는 것은 엔진 구조 세 가지뿐이고(오브젝트 목록, 이름 테이블,
  `ProcessEvent`), 그 밖의 모든 클래스, 프로퍼티, 함수는 **이름으로** 찾기 때문에 대부분의 게임 업데이트에도 깨지지 않습니다.
  게임 함수는 `ProcessEvent` 후킹을 통해 게임 스레드에서 호출됩니다.
- **안전:** 모든 기능은 크래시 가드 안에서 실행되며, 무언가가 없으면 해당 옵션이 비활성화됩니다.
</details>

## 크레딧

- [Dear ImGui](https://github.com/ocornut/imgui)(MIT)와 [MinHook](https://github.com/TsudaKageyu/minhook)(BSD-2-Clause)
- [Dumper-7](https://github.com/Encryqed/Dumper-7): 게임 클래스 분석에 사용
- [Inter](https://github.com/rsms/inter) 글꼴(SIL Open Font License 1.1). 중국어, 일본어, 한국어는 Windows 기본 글꼴 사용

## 면책 조항

Ketamine Menu는 팬이 만든 도구입니다. Saber Interactive, Boss Team Games, Clive Barker와 관련이 없으며 승인을 받지 않았습니다.
모든 상표는 각 소유자에게 있습니다. 사용에 따른 책임은 본인에게 있습니다.

## 라이선스

[MIT](LICENSE)
