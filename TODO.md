# TODO: Granular Roadmap & Active Tasks

## 1. High Priority: UI & Dashboard Consolidation
- [ ] **Consolidated Single-Page Dashboard:** Merge disparate settings panels and menu panels into a cohesive, tabbed/scrollable dashboard interface (`docs/DASHBOARD.md` / `StuffMenu`).
- [ ] **Interactive Tooltips & Visual Cues:** Add contextual hover descriptions and guidance markers for complex puzzle tuning parameters (randomizer bag types, lock delay, wall kick rules).
- [ ] **System Tray Integration:** Implement system tray icon (`SDL_CreateTray` in SDL3 or platform fallback) with quick actions:
  - [ ] Show/Hide Game Window.
  - [ ] Mute/Unmute Audio.
  - [ ] Quicksave / Save State.
  - [ ] Safe Quit Application & Kill Background Network Workers.
- [ ] **Live Telemetry & Diagnostics:** Connect in-engine `DebugInfoPanel` and `LogsPanel` to real-time performance graphs (FPS, frame time, draw calls, PCM visualizer buffer status).

---

## 2. Puzzle & Custom Editor Parity
- [ ] **Preview Viewport in Custom Game Editor:** Render an interactive real-time piece preview canvas adjacent to the 4x4 matrix grid in `CustomGameEditorControl`.
- [ ] **Import/Export Ruleset Serialization:** Wire JSON import and export for custom puzzle rulesets (`GameType`) to match web and Java formats.
- [ ] **Palette & Block Theme Authoring:** Expand editor to allow custom RGBA color sets, animation speed parameters, and special block triggers (bombs, wildcards, garbage converters).
- [ ] **Action Confirmation Modals:** Add confirmation dialogues on piece/rotation deletion to prevent accidental user data loss.

---

## 3. Network & Multiplayer
- [ ] **WebSocket Reconnection Resiliency:** Add exponential backoff reconnection logic in Poco network client on unexpected socket disconnects.
- [ ] **Matchmaking Lobby Polish:** Wire ping indicators, spectator slot toggling, and room password protection directly into `LobbyMenuPanel`.
- [ ] **Leaderboard Caching:** Persist recent online leaderboard query results locally to reduce network traffic on reconnects.

---

## 4. Libretro & Emulation Frontend
- [ ] **Core Downloader / Manager:** Add in-menu manifest fetching to automate downloading approved Libretro core binaries.
- [ ] **Shaders Submenu:** Expand CRT scanline options with customizable bloom, curvature, and phosphor mask toggles.
- [ ] **Audio Resampler Polish:** Implement dynamic sinc/cubic audio resampling in the ring buffer to eliminate audio crackle on slight timing discrepancies.

---

## 5. Bobcoin & Economy Integration
- [ ] **BobcoinManager Subsystem:** Connect `lib/bobcoin` client routines in `src/Engine/network/BobcoinManager.cpp`.
- [ ] **Wallet Dashboard UI:** Display current wallet balance, public address QR code, transaction history, and network synchronization status.
- [ ] **Proof-of-Play Mining Worker:** Implement background puzzle-reward computation thread with configurable CPU throttling.

---

## 6. Build & Infrastructure
- [ ] **Linux Launch Script Hardening:** Implement dependency autodetection and library rpath setup in `linux/bobsgame.sh` and `linux/prepare_for_launch.sh`.
- [ ] **Headless CI Verification Script:** Add a test script to validate compilation and verify headers without requiring an interactive X11/Wayland display.
