<p align="center">
  <img src="docs/banner.png" alt="Hellraiser Revival's Ketamine Menu" width="100%">
</p>

<p align="center">
  <a href="README.md">English</a> ·
  <a href="README.zh-CN.md">简体中文</a> ·
  <a href="README.ja.md">日本語</a> ·
  <a href="README.ko.md">한국어</a> ·
  <a href="README.ru.md">Русский</a> ·
  <a href="README.de.md">Deutsch</a> ·
  <a href="README.fr.md">Français</a> ·
  <b>Español</b> ·
  <a href="README.pt-BR.md">Português (Brasil)</a>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  Un trainer limpio dentro del juego para <b>Clive Barker's Hellraiser: Revival</b> (PC).<br>
  Pon un archivo en la carpeta del juego, pulsa <kbd>Insert</kbd> o <kbd>F8</kbd> y listo.
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
  <a href="#instalación">Instalación</a> ·
  <a href="#funciones">Funciones</a> ·
  <a href="#uso-del-menú">Uso</a> ·
  <a href="#faq--solución-de-problemas">FAQ</a> ·
  <a href="#desinstalación">Desinstalación</a> ·
  <a href="#compilar-desde-el-código-fuente">Compilar</a>
</p>

---

> [!TIP]
> **Haz una copia de tus partidas** antes de empezar: `%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`.

## Instalación

Solo necesitas un archivo y no hay que instalar nada en el PC (ni redistribuible de Visual C++, ni launcher).

1. **Descarga** el último `KetamineMenu-vX.Y.Z.zip` desde la [página de Releases](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest) y descomprímelo.
2. **Abre la carpeta del juego**: en Steam, clic derecho en *Clive Barker's Hellraiser: Revival* → **Administrar** (Manage) → **Ver archivos locales** (Browse local files).
   Después abre `Hellraiser` → `Binaries` → `Win64` (la carpeta que contiene `Hellraiser-Win64-Shipping.exe`).
3. **Copia `winmm.dll` en esa carpeta `Win64`.** Si quieres, copia también `KetamineMenu.ini` (ajustes por defecto).
4. **Inicia el juego**, carga una partida y pulsa <kbd>Insert</kbd> o <kbd>F8</kbd>.

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← opcional, si no se crea solo
```

**Vortex:** descárgalo desde la [página de Nexus Mods](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27) con *Mod Manager Download*.

**A mano, "extraer en la carpeta del juego":** usa `KetamineMenu-vX.Y.Z-Nexus.zip`. Ya trae las carpetas `Hellraiser\Binaries\Win64\`,
así que Vortex lo instala en el sitio correcto, o puedes extraerlo directamente en la carpeta del juego.

**Linux / Steam Deck (Proton):** Proton carga su propia `winmm.dll` en lugar de la del menú. En Steam, clic derecho en el juego → **Propiedades** (Properties) → **Opciones de lanzamiento** (Launch Options) y añade `WINEDLLOVERRIDES="winmm=n,b" %command%`. Si usas otras herramientas de lanzamiento (como `~/lsfg` o `gamemoderun`), ponlas antes de `%command%`, por ejemplo `WINEDLLOVERRIDES="winmm=n,b" ~/lsfg %command%`. No uses Decky Framegen (`~/fgmod/fgmod`) con el menú: borra `winmm.dll` en cada inicio.

> [!TIP]
> Si <kbd>Insert</kbd> / <kbd>F8</kbd> no hacen nada, abre `KetamineMenu.log` junto a la DLL: dice exactamente qué se encontró y qué no.
> Consulta las [FAQ](#faq--solución-de-problemas).

## Funciones

Cada opción busca los datos del juego **por su nombre mientras se ejecuta**. Si una actualización del juego elimina algo, esa opción se desactiva
(en gris) con el motivo en un tooltip, en lugar de cerrar el juego.

<table>
<tr>
<td width="50%" valign="top">

**Jugador**
- Modo dios, salud infinita
- Control deslizante de salud (cualquier valor)
- Sprint sin enfriamiento *(el juego no tiene resistencia)*
- Invisible para enemigos
- Muerte de un golpe, multiplicador de daño

**Combate**
- Munición infinita
- Armas cuerpo a cuerpo irrompibles
- Poderes de la Configuración Génesis sin coste de Sufrimiento
- Poderes sin enfriamiento, llenar Sufrimiento
- Desbloquear Telequinesis, Piroquinesis y Cadenas infernales antes que la historia
- Aim silencioso: tus disparos dan en la cabeza del enemigo más cercano a la mira, dentro de un círculo ajustable

**Movimiento**
- Volar y noclip hacia donde miras, con tus teclas de movimiento habituales o el mando
- Cámara libre (tu personaje se queda en su sitio)
- Multiplicadores de velocidad y altura de salto
- 3 posiciones guardadas + teletransporte a cualquier punto de control del nivel

</td>
<td width="50%" valign="top">

**ESP**
- Enemigos: caja, barra de salud, nombre, distancia, esqueleto, marcador de cabeza, chams, líneas guía, flechas fuera de pantalla
- Mundo: objetos en el suelo, contenedores de botín, puntos de guardado
- Alcance separado para enemigos y objetos

**Inventario**
- Añadir o quitar dinero
- Obtener cualquier objeto: munición, armas, mejoras, curación, materiales (lista sacada del propio juego)
- Desbloquear aspectos y colgantes de armas

**Mundo**
- Escala de tiempo (cámara lenta / avance rápido)
- Congelar enemigos, matar enemigos cercanos
- Editor de campo de visión (FOV, de 50° a 130°, en vivo), ocultar HUD
- Ganzúa automática: las cerraduras se abren solas
- Saltar los logotipos y avisos al iniciar (unos 30 s menos)

**Progreso**
- Ver objetivos activos y completados, completar uno, cambiar el nivel de la tienda

</td>
</tr>
</table>

### Capturas de pantalla

<table>
<tr>
<td><img src="docs/menu-player.png" alt="Jugador"></td>
<td><img src="docs/menu-combat.png" alt="Combate"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="Movimiento"></td>
<td><img src="docs/menu-esp.png" alt="ESP"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="Mundo"></td>
<td><img src="docs/menu-settings.png" alt="Ajustes"></td>
</tr>
</table>

## Uso del menú

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | Abrir / cerrar el menú (las dos teclas se cambian en **Ajustes**). Mientras está abierto, el ratón controla el menú y el juego ignora tus controles. |
| Atajos | Cualquier interruptor puede tener su propia tecla en **Ajustes → Atajos**. Funcionan con el menú cerrado y muestran una pequeña notificación. |
| Tooltips | Pasa el ratón por una opción para ver qué hace o por qué no está disponible. |
| Idioma | English, 简体中文, 日本語, 한국어, Русский, Deutsch, Français, Español, Português (Brasil): sigue el idioma de Windows; cámbialo en **Ajustes → Idioma**. |
| Escala de la interfaz | Se adapta a la resolución de la pantalla; ajústala con los botones − / + en **Ajustes**. |
| Pie | Versión del juego, CPU, GPU, RAM, resolución y FPS de un vistazo, abajo del menú. |
| Archivo de ajustes | Todo se guarda en `KetamineMenu.ini` junto a la DLL. **Ajustes → Restablecer la configuración** vuelve a los valores por defecto. |

> [!WARNING]
> Obtener objetos clave o completar objetivos puede romper secuencias guionizadas. **Guarda la partida antes.**

## Compatibilidad

- **Juego:** probado con las versiones `1.1.1.227384` (Steam, actualización de octubre de 2026) y `1.0.1.227219`. Otras versiones pueden funcionar:
  lo que no se encuentra aparece en gris.
- **Renderizado:** DirectX 12 (por defecto) y DirectX 11.
- **Otros mods:** el menú usa `winmm.dll`, así que no choca con ReShade (`dxgi.dll`) ni con UE4SS (`dwmapi.dll`).
- **Generación de fotogramas** (DLSS-G, FSR, XeSS FG): compatible, pero si el menú parpadea, desactiva la generación de fotogramas.

## FAQ / Solución de problemas

<details>
<summary><b>Insert / F8 no hacen nada</b></summary>

- Comprueba que `winmm.dll` está en `Hellraiser\Binaries\Win64` (junto a `Hellraiser-Win64-Shipping.exe`) y no en la carpeta raíz del juego.
- Abre `KetamineMenu.log` en la misma carpeta. Si no existe, la DLL no se cargó: revisa otra vez la carpeta y tu antivirus.
- Si cambiaste la tecla del menú, el pie del menú (y `KetamineMenu.ini`, `[Menu] Key=` / `Key2=`) muestra las teclas actuales.
</details>

<details>
<summary><b>Todo está en gris</b></summary>

Carga primero una partida: la mayoría de las opciones necesitan que exista el jugador. Si la cabecera dice *Motor no enganchado*, la versión del juego
cambió de una forma que el menú todavía no sabe manejar. Abre una issue y adjunta `KetamineMenu.log`.
</details>

<details>
<summary><b>Mi antivirus detecta la DLL</b></summary>

Los trainers se enganchan al renderizado y a la memoria del juego, algo que no gusta a las heurísticas de los antivirus. Es un falso positivo: el código
fuente está aquí, y cada versión se compila a partir de él con [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions).
También puedes [compilarlo tú mismo](#compilar-desde-el-código-fuente).
</details>

<details>
<summary><b>El juego se actualizó y algo dejó de funcionar</b></summary>

Las opciones que ya no se encuentran aparecen en gris con el motivo. Abre una issue con tu `KetamineMenu.log` y la versión del juego
(`Version.txt` en la carpeta del juego).
</details>

<details>
<summary><b>¿Cómo informo de un error?</b></summary>

[Abre una issue](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues) con lo que hiciste, lo que pasó y el archivo `KetamineMenu.log`
de tu última sesión (se sobrescribe cada vez que se inicia el juego).
</details>

## Desinstalación

Borra `winmm.dll`, `KetamineMenu.ini`, `KetamineMenu.log` (y `KetamineMenu-LICENSE.txt` si usaste el zip de Nexus) de `Hellraiser\Binaries\Win64`.
Con Vortex, quita el mod y luego borra el `.ini` y el `.log` que quedan. Nunca se modifica ningún archivo del juego.

## Compilar desde el código fuente

Requisitos: Windows, Visual Studio 2022 o posterior con la carga de trabajo *Desarrollo para el escritorio con C++*, CMake 3.25+.

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

La DLL queda en `build\Release\winmm.dll`. CMake descarga Dear ImGui y MinHook en versiones fijas, con sumas de verificación.
Al subir una etiqueta `v*` se compila automáticamente el zip de la release.

<details>
<summary><b>Cómo funciona</b></summary>

- **Carga:** el juego importa `winmm.dll`, así que Windows carga primero la nuestra desde la carpeta del juego. Cada función de `winmm` se reenvía a la
  DLL real del sistema y después el menú arranca en su propio hilo.
- **Overlay:** engancha DXGI `Present` (DirectX 11 y 12) con [MinHook](https://github.com/TsudaKageyu/minhook) y dibuja con
  [Dear ImGui](https://github.com/ocornut/imgui). No se dibuja nada con el menú cerrado (salvo las notificaciones y el ESP si está activado).
- **Acceso al juego:** lee los datos de reflexión de Unreal Engine 5. Solo tres estructuras del motor se buscan por patrón (la lista de objetos,
  la tabla de nombres y `ProcessEvent`); todas las clases, propiedades y funciones se buscan después **por nombre**, así que la mayoría de las
  actualizaciones del juego no lo rompen. Las funciones del juego se llaman en el hilo del juego mediante un hook de `ProcessEvent`.
- **Seguridad:** cada función se ejecuta tras una protección contra cierres y pasa a ser una opción en gris cuando falta algo.
</details>

## Créditos

- [Dear ImGui](https://github.com/ocornut/imgui) (MIT) y [MinHook](https://github.com/TsudaKageyu/minhook) (BSD-2-Clause)
- [Dumper-7](https://github.com/Encryqed/Dumper-7), para estudiar las clases del juego
- Fuente [Inter](https://github.com/rsms/inter) (SIL Open Font License 1.1); chino, japonés y coreano usan las fuentes de Windows

## Aviso legal

Ketamine Menu es una herramienta hecha por fans. No está afiliada ni respaldada por Saber Interactive, Boss Team Games ni Clive Barker.
Todas las marcas pertenecen a sus respectivos dueños. Úsalo bajo tu propia responsabilidad.

## Licencia

[MIT](LICENSE)
