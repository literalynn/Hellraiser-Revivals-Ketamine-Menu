<p align="center">
  <img src="docs/banner.png" alt="Hellraiser Revival's Ketamine Menu" width="100%">
</p>

<p align="center">
  <a href="README.md">English</a> ·
  <a href="README.zh-CN.md">简体中文</a> ·
  <a href="README.ja.md">日本語</a> ·
  <a href="README.ko.md">한국어</a> ·
  <b>Русский</b> ·
  <a href="README.de.md">Deutsch</a> ·
  <a href="README.fr.md">Français</a> ·
  <a href="README.es.md">Español</a> ·
  <a href="README.pt-BR.md">Português (Brasil)</a>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  Аккуратный внутриигровой трейнер для <b>Clive Barker's Hellraiser: Revival</b> (PC).<br>
  Положите один файл в папку игры, нажмите <kbd>Insert</kbd> или <kbd>F8</kbd> — готово.
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
  <a href="#установка">Установка</a> ·
  <a href="#возможности">Возможности</a> ·
  <a href="#как-пользоваться-меню">Использование</a> ·
  <a href="#faq--решение-проблем">FAQ</a> ·
  <a href="#удаление">Удаление</a> ·
  <a href="#сборка-из-исходников">Сборка</a>
</p>

---

> [!TIP]
> Перед началом **сделайте резервную копию сохранений**: `%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`.

## Установка

Нужен всего один файл, и ничего не нужно устанавливать на ПК (ни Visual C++ Redistributable, ни лаунчер).

1. **Скачайте** последний `KetamineMenu-vX.Y.Z.zip` со [страницы Releases](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest) и распакуйте его.
2. **Откройте папку игры**: в Steam щёлкните правой кнопкой по *Clive Barker's Hellraiser: Revival* → **Управление** (Manage) → **Просмотреть локальные файлы** (Browse local files).
   Затем откройте `Hellraiser` → `Binaries` → `Win64` (папку, где лежит `Hellraiser-Win64-Shipping.exe`).
3. **Скопируйте `winmm.dll` в эту папку `Win64`.** По желанию скопируйте туда же `KetamineMenu.ini` (настройки по умолчанию).
4. **Запустите игру**, загрузите сохранение и нажмите <kbd>Insert</kbd> или <kbd>F8</kbd>.

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← необязательно, иначе создаётся автоматически
```

**Vortex:** скачайте со [страницы на Nexus Mods](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27) кнопкой *Mod Manager Download*.

**Вручную, «распаковать в папку игры»:** используйте `KetamineMenu-vX.Y.Z-Nexus.zip`. В нём уже есть папки `Hellraiser\Binaries\Win64\`,
поэтому Vortex установит его куда нужно, а вручную его можно распаковать прямо в папку игры.

> [!TIP]
> Если <kbd>Insert</kbd> / <kbd>F8</kbd> ничего не делают, откройте `KetamineMenu.log` рядом с DLL: там точно написано, что найдено, а что нет.
> См. [FAQ](#faq--решение-проблем).

## Возможности

Каждая опция находит данные игры **по имени во время работы**. Если обновление игры что-то удалит, опция станет серой,
а причина появится во всплывающей подсказке — вместо вылета игры.

<table>
<tr>
<td width="50%" valign="top">

**Игрок**
- Режим бога, бесконечное здоровье
- Ползунок здоровья (любое значение)
- Без перезарядки бега *(выносливости в игре нет)*
- Невидимость для врагов
- Убийство с одного удара, множитель урона

**Бой**
- Бесконечные патроны
- Неломающееся оружие ближнего боя
- Способности Конфигурации Генезиса (Genesis Configuration) без затрат Страдания
- Без перезарядки способностей, восполнение Страдания
- Телекинез, пирокинез и адские цепи раньше, чем по сюжету

**Движение**
- Полёт и прохождение сквозь стены — туда, куда вы смотрите, обычными клавишами движения или геймпадом
- Свободная камера (персонаж остаётся на месте)
- Множители скорости и высоты прыжка
- 3 сохранённые позиции + телепорт к любой контрольной точке уровня

</td>
<td width="50%" valign="top">

**ESP**
- Враги: рамка, полоса здоровья, имя, расстояние, скелет, метка головы, подсветка, линии к врагам, стрелки за экраном
- Мир: предметы на земле, контейнеры с добычей, точки сохранения
- Отдельная дальность для врагов и объектов

**Инвентарь**
- Добавить или убрать деньги
- Получить любой предмет: патроны, оружие, улучшения, лечение, материалы (список берётся из самой игры)
- Открыть скины и брелоки для оружия

**Мир**
- Скорость времени (замедление / ускорение)
- Заморозить врагов, убить врагов рядом
- Редактор поля зрения (FOV) (от 50° до 130°, на лету), скрыть HUD
- Автовзлом: замки открываются сами
- Пропуск логотипов и предупреждений при запуске (около 30 с экономии)

**Прогресс**
- Активные и выполненные задания, выполнить задание, изменить уровень магазина

</td>
</tr>
</table>

### Скриншоты

<table>
<tr>
<td><img src="docs/menu-player.png" alt="Игрок"></td>
<td><img src="docs/menu-combat.png" alt="Бой"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="Движение"></td>
<td><img src="docs/menu-esp.png" alt="ESP"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="Мир"></td>
<td><img src="docs/menu-settings.png" alt="Настройки"></td>
</tr>
</table>

## Как пользоваться меню

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | Открыть / закрыть меню (обе клавиши меняются в **Настройках**). Пока меню открыто, мышь управляет меню, а игра не получает ваш ввод. |
| Горячие клавиши | Любому переключателю можно назначить свою клавишу в **Настройки → Горячие клавиши**. Они работают при закрытом меню и показывают небольшое уведомление. |
| Подсказки | Наведите курсор на опцию, чтобы увидеть, что она делает или почему недоступна. |
| Язык | English, 简体中文, 日本語, 한국어, Русский, Deutsch, Français, Español, Português (Brasil): сначала берётся язык Windows, сменить можно в **Настройки → Язык**. |
| Масштаб интерфейса | Подстраивается под разрешение экрана; меняется кнопками − / + в **Настройках**. |
| Нижняя строка | Версия игры, CPU, GPU, RAM, разрешение и FPS внизу меню. |
| Файл настроек | Всё сохраняется в `KetamineMenu.ini` рядом с DLL. **Настройки → Сбросить настройки** возвращает значения по умолчанию. |

> [!WARNING]
> Выдача ключевых предметов или выполнение заданий могут сломать сюжетные сцены. **Сначала сохранитесь.**

## Совместимость

- **Игра:** проверено на версиях `1.1.1.227384` (Steam, обновление октября 2026) и `1.0.1.227219`. Другие версии тоже могут работать:
  всё, что не удалось найти, становится серым.
- **Рендер:** DirectX 12 (по умолчанию) и DirectX 11.
- **Другие моды:** меню использует `winmm.dll`, поэтому не конфликтует с ReShade (`dxgi.dll`) и UE4SS (`dwmapi.dll`).
- **Генерация кадров** (DLSS-G, FSR, XeSS FG): поддерживается, но если меню мерцает, отключите генерацию кадров.

## FAQ / Решение проблем

<details>
<summary><b>Insert / F8 ничего не делают</b></summary>

- Проверьте, что `winmm.dll` лежит в `Hellraiser\Binaries\Win64` (рядом с `Hellraiser-Win64-Shipping.exe`), а не в корневой папке игры.
- Откройте `KetamineMenu.log` в той же папке. Если его нет, DLL не загрузилась: ещё раз проверьте папку и антивирус.
- Если вы меняли клавишу меню, текущие клавиши видны в нижней строке меню (и в `KetamineMenu.ini`, `[Menu] Key=` / `Key2=`).
</details>

<details>
<summary><b>Всё серое</b></summary>

Сначала загрузите сохранение: большинству опций нужен персонаж игрока. Если в заголовке написано *Движок не подключён*, версия игры изменилась так,
что меню пока не может с ней работать. Откройте issue и приложите `KetamineMenu.log`.
</details>

<details>
<summary><b>Антивирус ругается на DLL</b></summary>

Трейнеры перехватывают отрисовку и память игры, а эвристика антивирусов этого не любит. Это ложное срабатывание: исходный код лежит здесь,
и каждый релиз собирается из него через [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions).
Можно также [собрать его самостоятельно](#сборка-из-исходников).
</details>

<details>
<summary><b>После обновления игры что-то перестало работать</b></summary>

Опции, которые больше не удаётся найти, становятся серыми с указанием причины. Откройте issue, приложив `KetamineMenu.log` и версию игры
(`Version.txt` в папке игры).
</details>

<details>
<summary><b>Как сообщить об ошибке?</b></summary>

[Откройте issue](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues): что вы сделали, что произошло, и приложите файл `KetamineMenu.log`
из последней сессии (он перезаписывается при каждом запуске игры).
</details>

## Удаление

Удалите `winmm.dll`, `KetamineMenu.ini`, `KetamineMenu.log` (и `KetamineMenu-LICENSE.txt`, если вы ставили zip с Nexus) из `Hellraiser\Binaries\Win64`.
В Vortex удалите мод, затем удалите оставшиеся `.ini` и `.log`. Файлы игры никогда не изменяются.

## Сборка из исходников

Нужно: Windows, Visual Studio 2022 или новее с нагрузкой *Разработка классических приложений на C++*, CMake 3.25+.

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

DLL появится в `build\Release\winmm.dll`. Dear ImGui и MinHook скачиваются CMake в закреплённых версиях с проверкой контрольных сумм.
Пуш тега `v*` автоматически собирает zip релиза.

<details>
<summary><b>Как это работает</b></summary>

- **Загрузка:** игра импортирует `winmm.dll`, поэтому Windows сначала загружает наш файл из папки игры. Все функции `winmm` перенаправляются
  в настоящую системную DLL, после чего меню запускается в своём потоке.
- **Оверлей:** перехватывает DXGI `Present` (DirectX 11 и 12) с помощью [MinHook](https://github.com/TsudaKageyu/minhook) и рисует через
  [Dear ImGui](https://github.com/ocornut/imgui). Пока меню закрыто, ничего не рисуется (кроме уведомлений и включённого ESP).
- **Доступ к игре:** читает собственные данные рефлексии Unreal Engine 5. По сигнатурам ищутся только три структуры движка (список объектов,
  таблица имён и `ProcessEvent`); все классы, свойства и функции затем ищутся **по имени**, поэтому большинство обновлений игры его не ломают.
  Функции игры вызываются в игровом потоке через перехват `ProcessEvent`.
- **Безопасность:** каждая функция работает под защитой от вылетов и превращается в серую опцию, если чего-то не хватает.
</details>

## Благодарности

- [Dear ImGui](https://github.com/ocornut/imgui) (MIT) и [MinHook](https://github.com/TsudaKageyu/minhook) (BSD-2-Clause)
- [Dumper-7](https://github.com/Encryqed/Dumper-7) — для изучения классов игры
- Шрифт [Inter](https://github.com/rsms/inter) (SIL Open Font License 1.1); для китайского, японского и корейского — шрифты Windows

## Отказ от ответственности

Ketamine Menu — фанатский инструмент. Он не связан с Saber Interactive, Boss Team Games или Clive Barker и не одобрен ими.
Все товарные знаки принадлежат их владельцам. Используйте на свой страх и риск.

## Лицензия

[MIT](LICENSE)
