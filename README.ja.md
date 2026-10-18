<p align="center">
  <img src="docs/banner.png" alt="Hellraiser Revival's Ketamine Menu" width="100%">
</p>

<p align="center">
  <a href="README.md">English</a> ·
  <a href="README.zh-CN.md">简体中文</a> ·
  <b>日本語</b> ·
  <a href="README.ko.md">한국어</a> ·
  <a href="README.ru.md">Русский</a> ·
  <a href="README.de.md">Deutsch</a> ·
  <a href="README.fr.md">Français</a> ·
  <a href="README.es.md">Español</a> ·
  <a href="README.pt-BR.md">Português (Brasil)</a>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  <b>Clive Barker's Hellraiser: Revival</b>（PC）向けの、シンプルなゲーム内トレーナーです。<br>
  ゲームフォルダにファイルを 1 つ置いて、<kbd>Insert</kbd> か <kbd>F8</kbd> を押すだけ。
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
  <a href="#インストール">インストール</a> ·
  <a href="#機能">機能</a> ·
  <a href="#メニューの使い方">使い方</a> ·
  <a href="#faq--トラブルシューティング">FAQ</a> ·
  <a href="#アンインストール">アンインストール</a> ·
  <a href="#ソースからビルド">ビルド</a>
</p>

---

> [!TIP]
> 始める前に**セーブデータをバックアップ**してください：`%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`

## インストール

必要なのはファイル 1 つだけで、PC に何かをインストールする必要はありません（Visual C++ 再頒布可能パッケージもランチャーも不要）。

1. [Releases ページ](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest)から最新の `KetamineMenu-vX.Y.Z.zip` を**ダウンロード**して展開します。
2. **ゲームフォルダを開きます**：Steam で *Clive Barker's Hellraiser: Revival* を右クリック → **管理**（Manage）→ **ローカルファイルを閲覧**（Browse local files）。
   続けて `Hellraiser` → `Binaries` → `Win64`（`Hellraiser-Win64-Shipping.exe` があるフォルダ）を開きます。
3. **`winmm.dll` をその `Win64` フォルダにコピーします。** 必要なら `KetamineMenu.ini`（初期設定）も一緒にコピーできます。
4. **ゲームを起動**してセーブをロードし、<kbd>Insert</kbd> か <kbd>F8</kbd> を押します。

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← 任意。なければ自動で作成されます
```

**Vortex：** [Nexus Mods のページ](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27)で *Mod Manager Download* から入手できます。

**手動で「ゲームフォルダに展開」する場合：** 代わりに `KetamineMenu-vX.Y.Z-Nexus.zip` を使ってください。`Hellraiser\Binaries\Win64\`
のフォルダ構成が含まれているので、Vortex が正しい場所に入れてくれますし、ゲームフォルダにそのまま展開することもできます。

**Linux / Steam Deck（Proton）：** Proton はメニューのものではなく自前の `winmm.dll` を読み込みます。Steam でゲームを右クリック → **プロパティ**（Properties）→ **起動オプション**（Launch Options）に `WINEDLLOVERRIDES="winmm=n,b" %command%` を追加してください。

> [!TIP]
> <kbd>Insert</kbd> / <kbd>F8</kbd> を押しても何も起きない場合は、DLL と同じ場所にある `KetamineMenu.log` を開いてください。何が見つかり、何が見つからなかったかが書かれています。
> [FAQ](#faq--トラブルシューティング) も参照してください。

## 機能

すべてのオプションは、ゲームのデータを**実行時に名前で**探します。ゲームのアップデートで何かが削除された場合、そのオプションはクラッシュする代わりに
グレーアウトし、理由がツールチップに表示されます。

<table>
<tr>
<td width="50%" valign="top">

**プレイヤー**
- ゴッドモード、体力無限
- 体力スライダー（好きな値に設定）
- ダッシュのクールダウンなし *（このゲームにスタミナはありません）*
- 敵から見えなくなる
- 一撃必殺、ダメージ倍率

**戦闘**
- 弾薬無限
- 近接武器が壊れない
- ジェネシス構成（Genesis Configuration）の能力で苦痛を消費しない
- 能力のクールダウンなし、苦痛を満タンにする
- 念動力・発火能力・ヘルチェーンをストーリーより先にアンロック
- サイレントエイム：調整できる円の中で照準に最も近い敵の頭に弾が当たる

**移動**
- 飛行と壁抜け。見ている方向へ、いつもの移動キーやゲームパッドで操作
- フリーカメラ（キャラクターはその場に残ります）
- 移動速度とジャンプの高さの倍率
- 位置の保存 3 か所 + レベル内の任意のチェックポイントへテレポート

</td>
<td width="50%" valign="top">

**ESP**
- 敵：ボックス、体力バー、名前、距離、骨格、頭マーカー、シルエット強調、スナップライン、画面外の矢印
- ワールド：落ちているアイテム、戦利品コンテナ、セーブポイント
- 敵とオブジェクトで別々の表示距離

**インベントリ**
- お金を増やす・減らす
- 任意のアイテムを入手：弾薬、武器、アップグレード、回復アイテム、素材（リストはゲーム自体から作成）
- 武器スキンとチャームをアンロック

**ワールド**
- 時間の速さ（スローモーション / 早送り）
- 敵を停止、近くの敵を倒す
- 視野角（FOV）エディタ（50°〜130°、リアルタイム）、HUD 非表示
- 自動ピッキング：鍵が自動で開く
- 起動時のロゴと注意画面をスキップ（約 30 秒短縮）

**進行**
- 進行中・完了済みの目標を確認、目標を完了、ショップのレベルを変更

</td>
</tr>
</table>

### スクリーンショット

<table>
<tr>
<td><img src="docs/menu-player.png" alt="プレイヤー"></td>
<td><img src="docs/menu-combat.png" alt="戦闘"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="移動"></td>
<td><img src="docs/menu-esp.png" alt="ESP"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="ワールド"></td>
<td><img src="docs/menu-settings.png" alt="設定"></td>
</tr>
</table>

## メニューの使い方

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | メニューを開く / 閉じる（どちらのキーも **設定** で変更可能）。メニューを開いている間はマウスでメニューを操作し、ゲームは入力を受け付けません。 |
| ホットキー | どのスイッチにも **設定 → ホットキー** で専用のキーを割り当てられます。ホットキーはメニューを閉じていても使え、小さな通知が表示されます。 |
| ホバー | オプションにマウスを合わせると、その機能や使えない理由が表示されます。 |
| 言語 | English、简体中文、日本語、한국어、Русский、Deutsch、Français、Español、Português (Brasil)：最初は Windows の表示言語に合わせます。**設定 → 言語** で変更できます。 |
| UIサイズ | 画面の解像度に合わせて自動調整。**設定** の − / + ボタンで調整できます。 |
| フッター | メニュー下部にゲームのバージョン、CPU、GPU、RAM、解像度、FPS を表示します。 |
| 設定ファイル | すべての設定は DLL と同じ場所の `KetamineMenu.ini` に保存されます。**設定 → 設定をリセット** で初期値に戻せます。 |

> [!WARNING]
> 重要アイテムの入手や目標の完了は、スクリプトで進むシーンを壊すことがあります。**先にセーブしてください。**

## 互換性

- **ゲーム：** バージョン `1.1.1.227384`（Steam、2026 年 10 月のアップデート）と `1.0.1.227219` で動作確認済み。他のバージョンでも動く可能性があります：
  見つからないものはグレーアウトされます。
- **レンダラー：** DirectX 12（既定）と DirectX 11。
- **他の MOD：** このメニューは `winmm.dll` を使うので、ReShade（`dxgi.dll`）や UE4SS（`dwmapi.dll`）とは競合しません。
- **フレーム生成**（DLSS-G、FSR、XeSS FG）：対応していますが、メニューがちらつく場合はフレーム生成をオフにしてください。

## FAQ / トラブルシューティング

<details>
<summary><b>Insert / F8 を押しても何も起きない</b></summary>

- `winmm.dll` がゲームの一番上のフォルダではなく、`Hellraiser\Binaries\Win64`（`Hellraiser-Win64-Shipping.exe` と同じ場所）にあるか確認してください。
- 同じフォルダの `KetamineMenu.log` を開きます。このファイルがない場合、DLL は読み込まれていません：フォルダとウイルス対策ソフトをもう一度確認してください。
- メニューキーを変更した場合、メニューのフッター（と `KetamineMenu.ini` の `[Menu] Key=` / `Key2=`）に現在のキーが表示されます。
</details>

<details>
<summary><b>すべてグレーアウトしている</b></summary>

先にセーブをロードしてください：ほとんどのオプションはプレイヤーが存在している必要があります。ヘッダーに *エンジン未接続* と表示される場合は、
ゲームのバージョンがメニューで対応できない形で変わっています。issue を作成して `KetamineMenu.log` を添付してください。
</details>

<details>
<summary><b>ウイルス対策ソフトが DLL を検出する</b></summary>

トレーナーはゲームの描画やメモリにフックするため、ウイルス対策ソフトのヒューリスティック検出に引っかかりやすいです。これは誤検知です：ソースコードはここにあり、
すべてのリリースは [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions) でソースからビルドされています。
[自分でビルド](#ソースからビルド)することもできます。
</details>

<details>
<summary><b>ゲームのアップデート後に何かが動かなくなった</b></summary>

見つからなくなったオプションは理由とともにグレーアウトされます。`KetamineMenu.log` とゲームのバージョン（ゲームフォルダの `Version.txt`）を添えて issue を作成してください。
</details>

<details>
<summary><b>バグを報告するには？</b></summary>

[issue を作成](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues)して、何をしたか、何が起きたかを書き、最後のプレイの
`KetamineMenu.log`（ゲームを起動するたびに上書きされます）を添付してください。
</details>

## アンインストール

`Hellraiser\Binaries\Win64` から `winmm.dll`、`KetamineMenu.ini`、`KetamineMenu.log`（Nexus の zip を使った場合は `KetamineMenu-LICENSE.txt` も）を削除します。
Vortex の場合は MOD を削除してから、残った `.ini` と `.log` を削除してください。ゲームのファイルが変更されることはありません。

## ソースからビルド

必要なもの：Windows、Visual Studio 2022 以降（*C++ によるデスクトップ開発* ワークロード）、CMake 3.25 以上。

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

DLL は `build\Release\winmm.dll` に作成されます。Dear ImGui と MinHook は CMake が固定バージョンでチェックサム付きでダウンロードします。
`v*` タグをプッシュすると、リリース用の zip が自動でビルドされます。

<details>
<summary><b>仕組み</b></summary>

- **読み込み：** ゲームは `winmm.dll` をインポートしているので、Windows はゲームフォルダにあるこのファイルを先に読み込みます。`winmm` の関数はすべて
  本来のシステム DLL に転送され、その後メニューが専用スレッドで起動します。
- **オーバーレイ：** [MinHook](https://github.com/TsudaKageyu/minhook) で DXGI の `Present`（DirectX 11 と 12）をフックし、
  [Dear ImGui](https://github.com/ocornut/imgui) で描画します。メニューを閉じている間は何も描画しません（通知と有効にした ESP を除く）。
- **ゲームへのアクセス：** Unreal Engine 5 自身のリフレクション情報を読みます。パターンで探すのはエンジンの 3 つの構造だけ（オブジェクト一覧、
  名前テーブル、`ProcessEvent`）で、クラス・プロパティ・関数はすべて**名前で**探すため、ほとんどのアップデートでは壊れません。
  ゲームの関数は `ProcessEvent` のフックを通してゲームスレッドで呼び出されます。
- **安全性：** すべての機能はクラッシュガードの内側で動き、何かが見つからない場合はグレーアウトされたオプションになります。
</details>

## クレジット

- [Dear ImGui](https://github.com/ocornut/imgui)（MIT）と [MinHook](https://github.com/TsudaKageyu/minhook)（BSD-2-Clause）
- [Dumper-7](https://github.com/Encryqed/Dumper-7)：ゲームのクラスの調査に使用
- [Inter](https://github.com/rsms/inter) フォント（SIL Open Font License 1.1）。中国語・日本語・韓国語は Windows 標準のフォントを使用

## 免責事項

Ketamine Menu はファンが作ったツールです。Saber Interactive、Boss Team Games、Clive Barker とは一切関係がなく、承認も受けていません。
すべての商標はそれぞれの所有者に帰属します。自己責任でご利用ください。

## ライセンス

[MIT](LICENSE)
