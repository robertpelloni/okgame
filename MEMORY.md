# MEMORY: Architectural Notes & Conventions

## 1. Memory Management & Ownership
- **Smart Pointer Usage:** Raw pointers have been refactored to `std::shared_ptr` (`sp<T>`) and `std::weak_ptr` (`wp<T>`) with `std::make_shared` (`ms<T>()`) across `Engine`, `Map`, `Audio`, `Network`, and `Puzzle`.
- **Static Textures & Lifecycles:** Be cautious of static texture handles such as `GLUtils::blankTexture`—do not wrap static singleton resources in `std::shared_ptr` without a no-op custom deleter to prevent double-free crashes on shutdown.
- **Byte Buffers:** `GLUtils` manages texture and pixel data via `std::shared_ptr<ByteArray>`.

---

## 2. Thread Safety & Synchronization Conventions
- **Method Naming Convention:** Methods appending `_S` (e.g. `setGotFacebookResponse_S()`, `getGameSave_S()`) indicate thread-safe synchronization.
- **Mutex Variables:** Mutex primitives are named with a `_Mutex` suffix (e.g. `data_Mutex`, `queue_Mutex`).
- **Network Queues:** Inbound network packets (`_incomingGameTypes`, `_incomingGameSequences`) are protected via `std::mutex` locks.
- **Audio & Visualizer Callbacks:** PCM data streaming from SDL3/SDL_mixer callbacks into `libprojectM::ProjectM` must remain non-blocking. Audio buffers are fed via thread-safe ring buffers.

---

## 3. Subsystem Integrations

### Steamworks Integration (`SteamManager`)
- **AppID:** Defaults to development AppID `480` (Spacewar) when no external `steam_appid.txt` is detected.
- **Callbacks:** `SteamManager::update()` invokes `SteamAPI_RunCallbacks()` every frame from the main engine loop (`Main::run()`).
- **Cloud Storage:** Bi-directional sync in `GameSave::syncWithSteamCloud()` reconciles local timestamps with `SteamRemoteStorage` (`save.txt`).
- **Friends & Presence:** `SteamManager::getFriends()` integrates with in-game lobby and friend lists.

### Libretro Emulation Frontend (`LibretroGame`)
- **State Management:** Cycle through 10 save state slots (`.state0` to `.state9`) with PNG thumbnail snapshots generated via `stb_image_write.h`.
- **Rewind Ring Buffer:** Circular `std::deque` storing serialized core states for zero-latency gameplay rewind.
- **CRT Shader & Filters:** Hardware/software post-processing supports Nearest, Linear, HQ2X software scaler, Flat CRT, and Curved CRT scanline shaders.

### Audio Visualization (`ProjectM`)
- **Modern OpenGL Core Profile:** ProjectM shader headers require `#version 330 core` rather than deprecated `#version 330` for strict SDL3 context compatibility.
- **Autopilot Preset Switching:** Automatic preset cycling periodically rotates visualizer presets from `resources/presets` every 15 seconds, toggled via in-game settings.

---

## 4. Performance & Frame Sync Profiling Notes
- **Frame Timing:** High-frequency rendering and simulation ticks are governed by `System::updateRenderTimers()` and `System::updateStats()`.
- **VSync vs. No-VSync:** `GLUtils::usingVSync` delegates timing to the display swap chain, while non-vsync modes use precision sleep/delays (`justDelay(2)`) to prevent CPU starvation.
