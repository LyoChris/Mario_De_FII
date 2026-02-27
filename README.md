# Mario De FII

A 2D Mario-inspired platformer written in C++ using the WinBGIm graphics stack and MiniAudio.

The project includes:
- a classic level campaign (`level1.txt` ... `level8.txt`)
- a custom level workflow (create, save, load, play)
- enemy AI (Goombas and Piranha plants)
- power-ups (star, 1-up, fire flower)
- in-game menus, stats tracking, and bilingual UI (RO/EN)

---

## Table of Contents
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure)
- [Gameplay Controls](#gameplay-controls)
- [Map Editor Controls](#map-editor-controls)
- [Level File Format](#level-file-format)
- [Persistent Data](#persistent-data)
- [How to Build](#how-to-build)
- [How to Run](#how-to-run)
- [Known Constraints](#known-constraints)
- [Credits](#credits)

---

## Features

- **Main menu flow**: Start, Custom Levels, Controls, Settings, Credits, Exit.
- **Standard campaign**: 8 predefined levels selected from `LevelsMenu()`.
- **Custom levels**:
  - Map editor integrated in the game UI.
  - Dynamic custom level list loaded from/saved to `CUSTOMLEVELS.txt`.
- **Player mechanics**:
  - Walk, jump, climb vines, pause menu.
  - Fireball attack when fire power is active.
- **Enemies**:
  - Goombas with directional patrol and obstacle checks.
  - Pipe-based Piranha plants with timed emerge/hide behavior.
- **Collectibles and power-ups**:
  - Coins, 1-up mushrooms, stars, fire flowers.
- **Audio system**:
  - Sound effects + looping music tracks via MiniAudio.
- **Stats and progression data**:
  - Per-level stats (coins, enemies, time, score) for default and custom levels.

---

## Tech Stack

- **Language**: C++
- **Graphics**: WinBGIm / BGI compatibility layer (`graphics.h`, `winbgi.cxx`, etc.)
- **Audio**: [MiniAudio](https://miniaud.io/) single-header library (`miniaudio.h`)
- **Build system**: Visual Studio C++ project (`bgi.vcxproj`)
- **Platform assumptions in code**: Windows APIs (`windows.h`, `GetSystemMetrics`, Win32 key states)

---

## Project Structure

### Core game modules
- `main.cpp` - startup entry point, initializes map/graphics/audio, language selection, menu boot.
- `Game.cpp` - main game loop (`MarioGame()`), frame timing, movement/enemy/fireball ticks.
- `Mario.cpp` - player state machine, movement logic, jumping, climbing, collisions, level end/death handling.
- `Enemies.cpp` - Goomba and Piranha behavior + animation updates.
- `Colectibles.cpp` - projectile logic, collectible overlap redraw behavior, fireball-enemy interactions.
- `Colissions.cpp` - AABB collision helpers (`CheckBlock`, `CheckColec`).
- `Map.cpp` - level parsing, visible map-window rendering, entity spawn extraction.

### Menus, loading, editor
- `Menus.cpp` - all UI menus, controls screens, pause/game-over/level-clear flows, settings and credits.
- `Loader.cpp` - asset preloading (images), map reset, random helper, stats/custom-level persistence.
- `MapEditor.cpp` - in-game editor, save/load panels, tile selection and placement constraints.

### Data files
- `level1.txt` ... `level8.txt` - default campaign maps.
- `LEVELSTATS.txt` - campaign stat records.
- `CUSTOMLEVELS.txt` - custom level registry + stats.

### Graphics backend sources
- `winbgi.cxx`, `bgiout.cxx`, `drawing.cxx`, `mouse.cxx`, `text.cxx`, etc. - WinBGIm/BGI support implementation.

---

## Gameplay Controls

> The project also displays dedicated controls screens (`GameControlsEN.jpg` / `GameControlsRO.jpg`) from the Controls menu.

From gameplay logic (`Mario.cpp`):

- **Move left**: `A` or `Left Arrow`
- **Move right**: `D` or `Right Arrow`
- **Climb up vine**: `W` or `Up Arrow` (while on vine tiles)
- **Climb down vine**: `S` or `Down Arrow` (while on vine tiles)
- **Jump**: `Space`
- **Shoot fireball**: `C` (only when fire flower power is active)
- **Pause**: `Esc`

Menu navigation in keyboard-driven menus (pause/game-over/level-clear):
- `W` / `S` or arrow equivalents for selection movement
- `Enter` to confirm

Main menu and level selection screens are mouse-driven.

---

## Map Editor Controls

> The project also displays dedicated editor controls screens (`EditorControlsEN.jpg` / `EditorControlsRO.jpg`).

From `MapEditor.cpp`:

- **Toggle mode**: `C`
  - Edit mode: place blocks in the map grid
  - Select mode: choose current tile type
- **Move cursor in grid**: `W`, `A`, `S`, `D` (or arrow keys)
- **Select tile (in select mode)**: `A` / `D` (or left/right arrows)
- **Apply tile / confirm selection**: `Space`
- **Save map**: `M`
- **Load map**: `N`
- **Previous panel**: `J`
- **Next panel**: `L`
- **Back to custom menu**: `B`

Editor enforces specific placement rules (for example, flagpole and Goomba constraints) before accepting tile placement.

---

## Level File Format

Each level text file starts with:
1. **First value**: number of columns (`nc`)
2. **Then 20 rows** (`nl = 20`) of integer tile IDs

The game internally supports wide maps up to 1000 columns and displays them in horizontal panels.

### Tile IDs used by game/editor

- `0` = sky / empty
- `1` = brick block (solid)
- `2` = 1-up collectible spawn
- `3` = vine
- `4` = vine top
- `5` = Goomba spawn
- `7` = coin collectible spawn
- `8` = lucky block
- `9` = Mario spawn point
- `10` = used lucky block
- `11` = flagpole marker
- `12` = pipe body
- `13` = pipe head with Piranha behavior
- `14` = pipe head

Editor-only intermediate variants:
- `131`, `141` are used for right-oriented pipe variants while editing, then normalized on save.

---

## Persistent Data

### `LEVELSTATS.txt`
Stores built-in level stats, one row per campaign level:
- level file name
- display name (terminated by `%` in the stored format)
- coins, enemies, time, score

### `CUSTOMLEVELS.txt`
Stores custom level metadata:
- first line: number of custom menu entries
- following lines: level display name + stats (coins/enemies/time/score)

Custom level names are used to build the dynamic custom-level menu.

---

## How to Build

###! Recommended (Visual Studio on Windows)

1. Open `Mario_De_FII.sln` in Visual Studio.
2. Select configuration:
   - `Debug|Win32` or `Release|Win32`
3. Build the solution.

Project file confirms:
- Platform toolset: `v143`
- Target platform: `Win32`

###! Asset requirement

The executable expects many image/audio assets at runtime (JPG/GIF/WAV files referenced in `Loader.cpp`, `Menus.cpp`, `Sounds.cpp`).
Make sure those assets are present in the working directory alongside the executable.

---

## How to Run

1. Build the project in Visual Studio.
2. Run the generated executable from the project output folder.
3. On startup:
   - language selection screen appears
   - then the main menu (`MainMenu()`) is shown

---

## Known Constraints

- The runtime code is tightly coupled to Windows APIs and WinBGIm behavior.
- The project targets `Win32` in the provided `.vcxproj`.
- A large global-state architecture is used across modules (`extern` variables), so behavior depends on initialization order.
- The repository currently contains an old `README.html` from BGI docs; this `README.md` is the project-specific documentation.

---

## Credits

The in-game Credits screen lists contributors and acknowledgements.
From `Menus.cpp` credits section, key names include:
- Patranea Cosmin-Cristian
- Iftimi George-Daniel

If you plan to publish this repository publicly, consider expanding this section with:
- contributor roles
- license details for assets/sounds
- third-party attributions for WinBGIm/MiniAudio and any external artwork/audio
