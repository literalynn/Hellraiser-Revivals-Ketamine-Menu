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
  <b>Français</b> ·
  <a href="README.es.md">Español</a> ·
  <a href="README.pt-BR.md">Português (Brasil)</a>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  Un trainer in-game propre pour <b>Clive Barker's Hellraiser: Revival</b> (PC).<br>
  Un seul fichier dans le dossier du jeu, appuyez sur <kbd>Inser</kbd> ou <kbd>F8</kbd>, c'est tout.
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
  <a href="#installation">Installation</a> ·
  <a href="#fonctionnalités">Fonctionnalités</a> ·
  <a href="#utiliser-le-menu">Utilisation</a> ·
  <a href="#faq--dépannage">FAQ</a> ·
  <a href="#désinstallation">Désinstallation</a> ·
  <a href="#compiler-depuis-les-sources">Compiler</a>
</p>

---

> [!TIP]
> **Sauvegardez vos parties** avant de commencer : `%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`.

## Installation

Un seul fichier suffit, et rien à installer sur votre PC (pas de redistribuable Visual C++, pas de launcher).

1. **Téléchargez** le dernier `KetamineMenu-vX.Y.Z.zip` depuis la [page Releases](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest) et dézippez-le.
2. **Ouvrez le dossier du jeu** : dans Steam, clic droit sur *Clive Barker's Hellraiser: Revival* → **Gérer** (Manage) → **Parcourir les fichiers locaux** (Browse local files).
   Puis ouvrez `Hellraiser` → `Binaries` → `Win64` (le dossier qui contient `Hellraiser-Win64-Shipping.exe`).
3. **Copiez `winmm.dll` dans ce dossier `Win64`.** Vous pouvez aussi copier `KetamineMenu.ini` (réglages par défaut).
4. **Lancez le jeu**, chargez une sauvegarde et appuyez sur <kbd>Inser</kbd> ou <kbd>F8</kbd>.

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← facultatif, créé automatiquement sinon
```

**Vortex :** récupérez-le sur la [page Nexus Mods](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27) avec *Mod Manager Download*.

**À la main, « extraire dans le dossier du jeu » :** prenez plutôt `KetamineMenu-vX.Y.Z-Nexus.zip`. Il contient déjà les dossiers
`Hellraiser\Binaries\Win64\` : Vortex l'installe donc au bon endroit, ou vous pouvez l'extraire directement dans le dossier du jeu.

**Linux / Steam Deck (Proton) :** Proton charge sa propre `winmm.dll` au lieu de celle du menu. Dans Steam, clic droit sur le jeu → **Propriétés** (Properties) → **Options de lancement** (Launch Options) et ajoutez `WINEDLLOVERRIDES="winmm=n,b" %command%`.

> [!TIP]
> Si <kbd>Inser</kbd> / <kbd>F8</kbd> ne font rien, ouvrez `KetamineMenu.log` à côté de la DLL : il indique exactement ce qui a été trouvé et ce qui ne l'a pas été.
> Voir la [FAQ](#faq--dépannage).

## Fonctionnalités

Chaque option retrouve les données du jeu **par leur nom, en direct**. Si une mise à jour du jeu supprime quelque chose, l'option est grisée
avec la raison dans une infobulle, au lieu de faire planter le jeu.

<table>
<tr>
<td width="50%" valign="top">

**Joueur**
- Mode dieu, santé infinie
- Curseur de santé (n'importe quelle valeur)
- Sprint sans temps de recharge *(le jeu n'a pas d'endurance)*
- Invisible aux ennemis
- Mort en un coup, multiplicateur de dégâts

**Combat**
- Munitions infinies
- Armes de mêlée incassables
- Pouvoirs de la Configuration Genesis sans coût en Souffrance
- Pouvoirs sans recharge, remplir la Souffrance
- Débloquer Télékinésie, Pyrokinésie et Chaînes infernales avant l'histoire
- Visée silencieuse : vos tirs touchent la tête de l'ennemi le plus proche du viseur, dans un cercle réglable

**Déplacement**
- Vol et noclip vers là où vous regardez, avec vos touches de déplacement habituelles ou la manette
- Caméra libre (votre personnage reste sur place)
- Multiplicateurs de vitesse et de hauteur de saut
- 3 positions enregistrées + téléportation vers n'importe quel point de contrôle du niveau

</td>
<td width="50%" valign="top">

**ESP**
- Ennemis : boîte, barre de vie, nom, distance, squelette, marqueur de tête, chams, lignes de visée, flèches hors écran
- Monde : objets au sol, conteneurs de butin, points de sauvegarde
- Portée séparée pour les ennemis et les objets

**Inventaire**
- Ajouter ou retirer de l'argent
- Obtenir n'importe quel objet : munitions, armes, améliorations, soins, matériaux (liste tirée du jeu lui-même)
- Débloquer les skins et charms d'armes

**Monde**
- Vitesse du temps (ralenti / accéléré)
- Figer les ennemis, tuer les ennemis proches
- Éditeur de champ de vision (FOV, de 50° à 130°, en direct), masquer le HUD
- Crochetage auto : les serrures s'ouvrent toutes seules
- Passer les logos et avertissements au lancement (environ 30 s de gagnées)

**Progression**
- Voir les objectifs en cours et terminés, en terminer un, changer le niveau de la boutique

</td>
</tr>
</table>

### Captures d'écran

<table>
<tr>
<td><img src="docs/menu-player.png" alt="Joueur"></td>
<td><img src="docs/menu-combat.png" alt="Combat"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="Déplacement"></td>
<td><img src="docs/menu-esp.png" alt="ESP"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="Monde"></td>
<td><img src="docs/menu-settings.png" alt="Paramètres"></td>
</tr>
</table>

## Utiliser le menu

| | |
|---|---|
| <kbd>Inser</kbd> / <kbd>F8</kbd> | Ouvrir / fermer le menu (les deux touches se changent dans **Paramètres**). Tant qu'il est ouvert, la souris contrôle le menu et le jeu ignore vos commandes. |
| Raccourcis | Chaque interrupteur peut avoir sa propre touche dans **Paramètres → Raccourcis**. Ils marchent menu fermé et affichent une petite notification. |
| Survol | Survolez une option pour voir ce qu'elle fait, ou pourquoi elle est indisponible. |
| Langue | English, 简体中文, 日本語, 한국어, Русский, Deutsch, Français, Español, Português (Brasil) : suit la langue de Windows, à changer dans **Paramètres → Langue**. |
| Taille de l'interface | S'adapte à la résolution de l'écran ; ajustable avec les boutons − / + dans **Paramètres**. |
| Pied de page | Version du jeu, CPU, GPU, RAM, résolution et FPS en un coup d'œil, en bas du menu. |
| Fichier de réglages | Tout est enregistré dans `KetamineMenu.ini` à côté de la DLL. **Paramètres → Réinitialiser la configuration** remet les valeurs par défaut. |

> [!WARNING]
> Obtenir des objets clés ou terminer des objectifs peut casser des séquences scriptées. **Sauvegardez avant.**

## Compatibilité

- **Jeu :** testé avec les versions `1.1.1.227384` (Steam, mise à jour d'octobre 2026) et `1.0.1.227219`. D'autres versions peuvent marcher :
  tout ce qui est introuvable est grisé.
- **Rendu :** DirectX 12 (par défaut) et DirectX 11.
- **Autres mods :** le menu utilise `winmm.dll`, il n'entre donc pas en conflit avec ReShade (`dxgi.dll`) ni UE4SS (`dwmapi.dll`).
- **Génération d'images** (DLSS-G, FSR, XeSS FG) : prise en charge, mais si le menu clignote, désactivez la génération d'images.

## FAQ / Dépannage

<details>
<summary><b>Inser / F8 ne font rien</b></summary>

- Vérifiez que `winmm.dll` est dans `Hellraiser\Binaries\Win64` (à côté de `Hellraiser-Win64-Shipping.exe`), pas dans le dossier racine du jeu.
- Ouvrez `KetamineMenu.log` dans le même dossier. S'il n'existe pas, la DLL n'a pas été chargée : vérifiez à nouveau le dossier et votre antivirus.
- Si vous avez changé la touche du menu, le pied de page du menu (et `KetamineMenu.ini`, `[Menu] Key=` / `Key2=`) affiche les touches actuelles.
</details>

<details>
<summary><b>Tout est grisé</b></summary>

Chargez d'abord une sauvegarde : la plupart des options ont besoin que le joueur existe. Si l'en-tête affiche *Moteur non accroché*, la version du jeu
a changé d'une façon que le menu ne gère pas encore. Ouvrez une issue et joignez `KetamineMenu.log`.
</details>

<details>
<summary><b>Mon antivirus signale la DLL</b></summary>

Les trainers s'accrochent au rendu et à la mémoire d'un jeu, ce que les heuristiques des antivirus n'aiment pas. C'est un faux positif : le code source
est ici, et chaque version est compilée à partir de lui par [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions).
Vous pouvez aussi [le compiler vous-même](#compiler-depuis-les-sources).
</details>

<details>
<summary><b>Le jeu a été mis à jour et quelque chose ne marche plus</b></summary>

Les options introuvables sont grisées avec la raison. Ouvrez une issue avec votre `KetamineMenu.log` et la version du jeu
(`Version.txt` dans le dossier du jeu).
</details>

<details>
<summary><b>Comment signaler un bug ?</b></summary>

[Ouvrez une issue](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues) avec ce que vous avez fait, ce qui s'est passé, et le fichier
`KetamineMenu.log` de votre dernière session (il est écrasé à chaque lancement du jeu).
</details>

## Désinstallation

Supprimez `winmm.dll`, `KetamineMenu.ini`, `KetamineMenu.log` (et `KetamineMenu-LICENSE.txt` si vous avez pris le zip Nexus) de
`Hellraiser\Binaries\Win64`. Avec Vortex, retirez le mod puis supprimez le `.ini` et le `.log` qui restent. Aucun fichier du jeu n'est jamais modifié.

## Compiler depuis les sources

Prérequis : Windows, Visual Studio 2022 ou plus récent avec la charge de travail *Développement Desktop en C++*, CMake 3.25+.

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

La DLL est `build\Release\winmm.dll`. Dear ImGui et MinHook sont téléchargés par CMake dans des versions fixées, avec vérification des sommes de contrôle.
Pousser un tag `v*` compile automatiquement le zip de la release.

<details>
<summary><b>Comment ça marche</b></summary>

- **Chargement :** le jeu importe `winmm.dll`, donc Windows charge d'abord la nôtre depuis le dossier du jeu. Chaque fonction `winmm` est redirigée
  vers la vraie DLL système, puis le menu démarre dans son propre thread.
- **Overlay :** hooke DXGI `Present` (DirectX 11 et 12) avec [MinHook](https://github.com/TsudaKageyu/minhook) et dessine avec
  [Dear ImGui](https://github.com/ocornut/imgui). Rien n'est affiché quand le menu est fermé (sauf les notifications et l'ESP s'il est activé).
- **Accès au jeu :** lit les données de réflexion d'Unreal Engine 5. Seules trois structures du moteur sont trouvées par signature (la liste des objets,
  la table des noms et `ProcessEvent`) ; toutes les classes, propriétés et fonctions sont ensuite cherchées **par leur nom**, donc la plupart des mises
  à jour du jeu ne le cassent pas. Les fonctions du jeu sont appelées sur le thread du jeu via un hook de `ProcessEvent`.
- **Sécurité :** chaque fonctionnalité tourne derrière une protection anti-crash et devient une option grisée quand il manque quelque chose.
</details>

## Crédits

- [Dear ImGui](https://github.com/ocornut/imgui) (MIT) et [MinHook](https://github.com/TsudaKageyu/minhook) (BSD-2-Clause)
- [Dumper-7](https://github.com/Encryqed/Dumper-7), pour étudier les classes du jeu
- Police [Inter](https://github.com/rsms/inter) (SIL Open Font License 1.1) ; le chinois, le japonais et le coréen utilisent les polices de Windows

## Avertissement

Ketamine Menu est un outil de fan. Il n'est ni affilié à Saber Interactive, Boss Team Games ou Clive Barker, ni approuvé par eux.
Toutes les marques appartiennent à leurs propriétaires respectifs. Utilisation à vos risques.

## Licence

[MIT](LICENSE)
