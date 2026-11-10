# Consolidated Unified Engine Dashboard

Welcome to the unified **OKGame / bob's game** Command & Operations Dashboard. This document brings together all operational telemetry, subsystem statuses, UI controls, and live workflows into a singular high-value interface.

---

## 1. High-Value Priority Control Center

| System Component | Status | Primary Action / Control | Tooltip & Guidance |
| :--- | :--- | :--- | :--- |
| **Puzzle Engine Core** |  ACTIVE | `GameType` / `Grid` | *[?] 1:1 cross-platform deterministic block physics, wall kicks, and bag randomizer.* |
| **Custom Ruleset Editor** |  ONLINE | `CustomGameEditorControl` | *[?] Direct matrix cell toggling, multiform rotations, and piece duplication.* |
| **Music Visualizer** |  ACTIVE | ProjectM & MilkDrop3 | *[?] Dynamic post-mix PCM visualization with GLSL 330 core shaders & autopilot.* |
| **Libretro Emulator** |  ONLINE | `LibretroGame` Frontend | *[?] Multi-slot save states (0-9), rewind buffers, CRT scanline shaders, and core association.* |
| **Steamworks SDK** |  POLISHED | `SteamManager` | *[?] AppID 480/real, achievements, cloud sync (`save.txt`), and friend list integration.* |
| **Multiplayer Network** |  READY | Poco C++ WebSockets | *[?] Real-time matchmaking rooms, synchronized opponent grids, and global stats.* |
| **Virtual Economy** |  PENDING | `BobcoinManager` | *[?] Proof-of-play tokens, wallet balance tracking, and tournament transactions.* |
| **System Tray Lifecycle** |  INTEGRATED | Tray & Background Ops | *[?] Quick window minimize/restore, audio mute, quicksave, and graceful server/process quit.* |

---

## 2. Unified Feature & Navigation Workflow

Rather than navigating fragmented, deeply nested menus, all major operational domains are grouped into consolidated panels:

```
[ UNIFIED CONTROL PANEL ]
├── 1. GAMEPLAY & EDITOR HUB (Highest Prominence)
│   ├── Instant Play: Marathon, Classic, Battle, Custom Game
│   ├── Custom Game Ruleset Authoring:
│   │   ├── Piece Matrix Toggle (4x4 grid)
│   │   ├── Rotation Controls (Add, Clear, Duplicate, Next, Previous)
│   │   └── Rules: Gravity Curve, Lock Delay, Bag Randomizer, Hold Queue
│   └── Live Piece Preview & Statistics
│
├── 2. AUDIO & VISUALIZATION COMMAND
│   ├── Audio Mixing: Volume master/BGM/SFX, SDL3/SDL_mixer buffer
│   ├── Visualizer Engine: ProjectM enabled/disabled
│   ├── Preset Gallery: Instant preset switch (F3 / F4 keys)
│   └── Autopilot Mode: Auto-cycle presets every 15 seconds
│
├── 3. EMULATION & RETRO GAMING (nD)
│   ├── ROM Selector & Compressed Zip Extraction (`Poco::Zip`)
│   ├── Save State Manager: 10 visual thumbnail slots
│   ├── Retro Filters: Nearest, Linear, HQ2X Upscaler
│   ├── CRT Shaders: Flat Scanlines, Curved CRT Distortion
│   └── Rewind Buffer: Real-time gameplay reversal
│
├── 4. ONLINE LOBBY, COMMUNITY & STEAM
│   ├── Matchmaking Lobby: Public/Private rooms, spectator mode
│   ├── Steam Integration:
│   │   ├── Steam Overlay & Achievements
│   │   ├── Friends List: Invite / Join Steam Friends
│   │   └── Steam Cloud: Bidirectional `save.txt` synchronization
│   └── High Scores & Leaderboards
│
└── 5. SYSTEM TRAY & SERVER PROCESS LIFECYCLE
    ├── System Tray Menu:
    │   ├── "Show / Focus Game Window"
    │   ├── "Mute / Unmute Audio"
    │   ├── "Quicksave Game State"
    │   └── "Gracefully Shut Down Servers & Quit Game"
    └── Background Worker Health: Poco WebSocket thread, CTPL thread pool
```

---

## 3. Performance & Frame Sync Profiling Telemetry

Real-time frame regulation operates under two distinct modes:

1. **Hardware VSync (`GLUtils::usingVSync = true`):**
   - Timing delegated to display swap chain (`doSwap()`).
   - Frame sync updates `System::updateRenderTimers()` and `System::updateStats()`.
   - Low CPU overhead with smooth refresh matching display panel frequency.

2. **Decoupled Non-VSync (`GLUtils::usingVSync = false`):**
   - Precise 16ms simulation tick enforcement (`System::getTotalRenderTicksPassed() >= 16`).
   - Micro-delay regulation via `justDelay(2)` prevents thread spinning and CPU overheating.
   - High-frequency input polling for frame-perfect tournament reactions.

---

## 4. Subsystem Verification Checklist

- [x] Modern C++ Smart Pointer Refactoring across all subsystems.
- [x] ProjectM Core Profile `#version 330 core` shader compilation.
- [x] Native Custom Game Editor with interactive rotation matrix and piece duplication.
- [x] Steamworks SDK hooks with Cloud Save timestamp comparison and friends lookup.
- [x] Consolidated Dashboard documentation unifying all engine functions.
