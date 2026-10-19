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
  <a href="README.es.md">Español</a> ·
  <b>Português (Brasil)</b>
</p>

<h1 align="center">Hellraiser Revival's Ketamine Menu</h1>

<p align="center">
  Um trainer limpo dentro do jogo para <b>Clive Barker's Hellraiser: Revival</b> (PC).<br>
  Coloque um arquivo na pasta do jogo, aperte <kbd>Insert</kbd> ou <kbd>F8</kbd> e pronto.
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
  <a href="#instalação">Instalação</a> ·
  <a href="#recursos">Recursos</a> ·
  <a href="#usando-o-menu">Uso</a> ·
  <a href="#faq--solução-de-problemas">FAQ</a> ·
  <a href="#desinstalação">Desinstalação</a> ·
  <a href="#compilar-a-partir-do-código-fonte">Compilar</a>
</p>

---

> [!TIP]
> **Faça backup dos seus saves** antes de começar: `%LOCALAPPDATA%\Hellraiser\Saved\SaveGames`.

## Instalação

Você só precisa de um arquivo e não tem nada para instalar no PC (nada de Visual C++ Redistributable, nada de launcher).

1. **Baixe** o `KetamineMenu-vX.Y.Z.zip` mais recente na [página de Releases](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/releases/latest) e extraia.
2. **Abra a pasta do jogo**: na Steam, clique com o botão direito em *Clive Barker's Hellraiser: Revival* → **Gerenciar** (Manage) → **Explorar arquivos locais** (Browse local files).
   Depois abra `Hellraiser` → `Binaries` → `Win64` (a pasta que tem o `Hellraiser-Win64-Shipping.exe`).
3. **Copie o `winmm.dll` para essa pasta `Win64`.** Se quiser, copie também o `KetamineMenu.ini` (configurações padrão).
4. **Inicie o jogo**, carregue um save e aperte <kbd>Insert</kbd> ou <kbd>F8</kbd>.

```
Clive Barker's Hellraiser - Revival\
└─ Hellraiser\
   └─ Binaries\
      └─ Win64\
         ├─ Hellraiser-Win64-Shipping.exe
         ├─ winmm.dll            ← Ketamine Menu
         └─ KetamineMenu.ini     ← opcional, senão é criado automaticamente
```

**Vortex:** baixe na [página do Nexus Mods](https://www.nexusmods.com/clivebarkershellraiserrevival/mods/27) com *Mod Manager Download*.

**Manual, "extrair na pasta do jogo":** use o `KetamineMenu-vX.Y.Z-Nexus.zip`. Ele já vem com as pastas `Hellraiser\Binaries\Win64\`,
então o Vortex instala no lugar certo, ou você pode extrair direto na pasta do jogo.

**Linux / Steam Deck (Proton):** O Proton carrega o próprio `winmm.dll` em vez do do menu. Na Steam, clique com o botão direito no jogo → **Propriedades** (Properties) → **Opções de inicialização** (Launch Options) e adicione `WINEDLLOVERRIDES="winmm=n,b" %command%`. Se você usa outras ferramentas de inicialização (como `~/lsfg` ou `gamemoderun`), coloque-as antes de `%command%`, por exemplo `WINEDLLOVERRIDES="winmm=n,b" ~/lsfg %command%`. Não use o Decky Framegen (`~/fgmod/fgmod`) com o menu: ele apaga o `winmm.dll` a cada inicialização.

> [!TIP]
> Se <kbd>Insert</kbd> / <kbd>F8</kbd> não fizerem nada, abra o `KetamineMenu.log` ao lado da DLL: ele diz exatamente o que foi encontrado e o que não foi.
> Veja o [FAQ](#faq--solução-de-problemas).

## Recursos

Cada opção encontra os dados do jogo **pelo nome, em tempo de execução**. Se uma atualização do jogo remover algo, a opção fica cinza com o motivo
na dica, em vez de fechar o jogo.

<table>
<tr>
<td width="50%" valign="top">

**Jogador**
- Modo deus, vida infinita
- Controle deslizante de vida (qualquer valor)
- Corrida sem recarga *(o jogo não tem stamina)*
- Invisível para inimigos
- Morte com um golpe, multiplicador de dano

**Combate**
- Munição infinita
- Armas corpo a corpo inquebráveis
- Poderes da Configuração Gênesis sem custo de Sofrimento
- Poderes sem recarga, encher o Sofrimento
- Desbloquear Telecinese, Pirocinese e Correntes infernais antes da história
- Mira silenciosa: seus tiros acertam a cabeça do inimigo mais perto da mira, dentro de um círculo ajustável

**Movimento**
- Voar e noclip para onde você olha, com as teclas de movimento de sempre ou o controle
- Câmera livre (seu personagem fica parado)
- Multiplicadores de velocidade e altura do pulo
- 3 posições salvas + teletransporte para qualquer checkpoint do nível

</td>
<td width="50%" valign="top">

**ESP**
- Inimigos: caixa, barra de vida, nome, distância, esqueleto, marcador de cabeça, chams, linhas guia, setas fora da tela
- Mundo: itens no chão, contêineres de loot, pontos de save
- Alcance separado para inimigos e objetos

**Inventário**
- Adicionar ou remover dinheiro
- Pegar qualquer item: munição, armas, melhorias, cura, materiais (lista tirada do próprio jogo)
- Desbloquear skins e pingentes de armas

**Mundo**
- Escala de tempo (câmera lenta / acelerar)
- Congelar inimigos, matar inimigos próximos
- Editor de campo de visão (FOV, de 50° a 130°, ao vivo), ocultar HUD
- Arrombamento automático: as fechaduras abrem sozinhas
- Pular os logos e avisos ao iniciar (uns 30 s a menos)

**Progresso**
- Ver objetivos ativos e concluídos, concluir um, mudar o nível da loja

</td>
</tr>
</table>

### Capturas de tela

<table>
<tr>
<td><img src="docs/menu-player.png" alt="Jogador"></td>
<td><img src="docs/menu-combat.png" alt="Combate"></td>
</tr>
<tr>
<td><img src="docs/menu-movement.png" alt="Movimento"></td>
<td><img src="docs/menu-esp.png" alt="ESP"></td>
</tr>
<tr>
<td><img src="docs/menu-world.png" alt="Mundo"></td>
<td><img src="docs/menu-settings.png" alt="Configurações"></td>
</tr>
</table>

## Usando o menu

| | |
|---|---|
| <kbd>Insert</kbd> / <kbd>F8</kbd> | Abrir / fechar o menu (as duas teclas podem ser trocadas em **Configurações**). Enquanto ele está aberto, o mouse controla o menu e o jogo ignora seus comandos. |
| Atalhos | Qualquer interruptor pode ter sua própria tecla em **Configurações → Atalhos**. Eles funcionam com o menu fechado e mostram uma pequena notificação. |
| Dicas | Passe o mouse sobre uma opção para ver o que ela faz ou por que está indisponível. |
| Idioma | English, 简体中文, 日本語, 한국어, Русский, Deutsch, Français, Español, Português (Brasil): segue o idioma do Windows; troque em **Configurações → Idioma**. |
| Escala da interface | Acompanha a resolução da tela; ajuste com os botões − / + em **Configurações**. |
| Rodapé | Versão do jogo, CPU, GPU, RAM, resolução e FPS num relance, na parte de baixo do menu. |
| Arquivo de configurações | Tudo fica salvo no `KetamineMenu.ini` ao lado da DLL. **Configurações → Redefinir a configuração** volta aos valores padrão. |

> [!WARNING]
> Pegar itens-chave ou concluir objetivos pode quebrar sequências roteirizadas. **Salve o jogo antes.**

## Compatibilidade

- **Jogo:** testado nas versões `1.1.1.227384` (Steam, atualização de outubro de 2026) e `1.0.1.227219`. Outras versões podem funcionar:
  o que não for encontrado fica cinza.
- **Renderização:** DirectX 12 (padrão) e DirectX 11.
- **Outros mods:** o menu usa `winmm.dll`, então não conflita com ReShade (`dxgi.dll`) nem com UE4SS (`dwmapi.dll`).
- **Geração de quadros** (DLSS-G, FSR, XeSS FG): suportada, mas se o menu piscar, desligue a geração de quadros.

## FAQ / Solução de problemas

<details>
<summary><b>Insert / F8 não fazem nada</b></summary>

- Confira se o `winmm.dll` está em `Hellraiser\Binaries\Win64` (ao lado do `Hellraiser-Win64-Shipping.exe`) e não na pasta raiz do jogo.
- Abra o `KetamineMenu.log` na mesma pasta. Se ele não existir, a DLL não foi carregada: confira de novo a pasta e o seu antivírus.
- Se você trocou a tecla do menu, o rodapé do menu (e o `KetamineMenu.ini`, `[Menu] Key=` / `Key2=`) mostra as teclas atuais.
</details>

<details>
<summary><b>Está tudo cinza</b></summary>

Carregue um save primeiro: a maioria das opções precisa que o jogador exista. Se o cabeçalho disser *Motor não conectado*, a versão do jogo mudou de um
jeito que o menu ainda não consegue lidar. Abra uma issue e anexe o `KetamineMenu.log`.
</details>

<details>
<summary><b>Meu antivírus acusa a DLL</b></summary>

Trainers se conectam à renderização e à memória do jogo, o que as heurísticas dos antivírus não gostam. É um falso positivo: o código-fonte está aqui,
e cada versão é compilada a partir dele pelo [GitHub Actions](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/actions).
Você também pode [compilar você mesmo](#compilar-a-partir-do-código-fonte).
</details>

<details>
<summary><b>O jogo atualizou e algo parou de funcionar</b></summary>

As opções que não são mais encontradas ficam cinza com o motivo. Abra uma issue com o seu `KetamineMenu.log` e a versão do jogo
(`Version.txt` na pasta do jogo).
</details>

<details>
<summary><b>Como relato um bug?</b></summary>

[Abra uma issue](https://github.com/literalynn/Hellraiser-Revivals-Ketamine-Menu/issues) com o que você fez, o que aconteceu e o arquivo `KetamineMenu.log`
da sua última sessão (ele é sobrescrito toda vez que o jogo inicia).
</details>

## Desinstalação

Apague `winmm.dll`, `KetamineMenu.ini`, `KetamineMenu.log` (e `KetamineMenu-LICENSE.txt` se você usou o zip do Nexus) de `Hellraiser\Binaries\Win64`.
Com o Vortex, remova o mod e depois apague o `.ini` e o `.log` que sobrarem. Nenhum arquivo do jogo é modificado.

## Compilar a partir do código-fonte

Requisitos: Windows, Visual Studio 2022 ou mais recente com a carga de trabalho *Desenvolvimento para desktop com C++*, CMake 3.25+.

```bash
cmake -S . -B build -A x64
cmake --build build --config Release
ctest --test-dir build -C Release
```

A DLL fica em `build\Release\winmm.dll`. O CMake baixa o Dear ImGui e o MinHook em versões fixas, com checksums.
Enviar uma tag `v*` compila o zip da release automaticamente.

<details>
<summary><b>Como funciona</b></summary>

- **Carregamento:** o jogo importa `winmm.dll`, então o Windows carrega primeiro a nossa, da pasta do jogo. Cada função de `winmm` é repassada para a
  DLL real do sistema e depois o menu inicia na sua própria thread.
- **Overlay:** faz hook no `Present` do DXGI (DirectX 11 e 12) com o [MinHook](https://github.com/TsudaKageyu/minhook) e desenha com o
  [Dear ImGui](https://github.com/ocornut/imgui). Nada é desenhado com o menu fechado (exceto notificações e o ESP, se ativado).
- **Acesso ao jogo:** lê os dados de reflexão da própria Unreal Engine 5. Só três estruturas da engine são achadas por padrão de bytes (a lista de objetos,
  a tabela de nomes e `ProcessEvent`); todas as classes, propriedades e funções são procuradas depois **pelo nome**, então a maioria das atualizações
  do jogo não quebra nada. As funções do jogo são chamadas na thread do jogo por meio de um hook no `ProcessEvent`.
- **Segurança:** cada recurso roda atrás de uma proteção contra crashes e vira uma opção cinza quando falta alguma coisa.
</details>

## Créditos

- [Dear ImGui](https://github.com/ocornut/imgui) (MIT) e [MinHook](https://github.com/TsudaKageyu/minhook) (BSD-2-Clause)
- [Dumper-7](https://github.com/Encryqed/Dumper-7), usado para estudar as classes do jogo
- Fonte [Inter](https://github.com/rsms/inter) (SIL Open Font License 1.1); chinês, japonês e coreano usam as fontes do Windows

## Aviso legal

Ketamine Menu é uma ferramenta feita por fãs. Não é afiliada nem endossada pela Saber Interactive, Boss Team Games ou Clive Barker.
Todas as marcas pertencem aos seus respectivos donos. Use por sua conta e risco.

## Licença

[MIT](LICENSE)
