# IDEAS: okgame (C++) Improvements

## 1. Build System & Toolchain
- **Vcpkg / Conan Integration:** The `lib/` folder contains dozens of deeply vendored submodules (Boost, SDL, Poco, libpng, etc.). Transitioning to a package manager like `vcpkg` or `Conan` would simplify the CMake script immensely and speed up native build times.
- **CMake Modernization:** Upgrade all `CMakeLists.txt` to strictly use `target_link_libraries` (Modern CMake) rather than legacy `include_directories` and global variables to prevent dependency bleeding.
- **Automated Dockerized Headless CI:** Setup a containerized Linux build pipeline with pre-installed X11/Mesa headers for instantaneous automated pull request verification.

## 2. Engine Architecture & Performance
- **EnTT / ECS:** The current hierarchy (`EnginePart`, `Entity`, `Map`) is highly object-oriented. Migrating game objects to an Entity-Component-System (like `EnTT`) would vastly improve cache locality and iteration speed, especially for complex RPG maps.
- **Vulkan / SDL3 GPU API:** The rendering is currently bound to OpenGL (Core Profile). Preparing the abstraction layer to target Vulkan via SDL3's GPU API would future-proof the engine and reduce driver overhead on low-end hardware.
- **Adaptive Frame Delays:** Implement PID-controller-based or microsecond-precision adaptive sleeps in `Main::justDelay` during decoupled non-vsync frames to maintain 1000 FPS responsiveness with negligible CPU idling draw.

## 3. Lua Bindings
- **Sol3 / Sol2:** The engine uses manual Lua C-API stack manipulation. Integrating `Sol2` or `Sol3` would provide type-safe, elegant C++17 bindings for the Lua scripts.
- **Hot Reloading:** Implement a directory watcher (`efsw` or similar) to hot-reload Lua puzzle scripts and shaders while the engine is running.

## 4. Audio & Visualizer Pipeline
- **miniaudio:** Replace `SDL_mixer` or heavily patch it with `miniaudio.h`. `miniaudio` is a single-header library that provides incredibly low-latency mixing, which is critical for frame-perfect puzzle game sound effects.
- **Direct GPU Spectrum FFT:** Move FFT frequency calculation from CPU into compute shaders before passing texture data to ProjectM presets.

## 5. System Tray & Background Service
- **SDL3 Tray API:** Leverage native `SDL_CreateTray` in SDL3 to provide continuous background presence, audio notifications, pause-on-minimize, and quick-quit hooks without requiring third-party platform UI libraries.
- **WebAssembly (Emscripten) Unified Build:** If `okgame` achieves a clean SDL3/Vulkan build, an Emscripten target could be revived. This would allow the absolute native 1:1 C++ code to run in the browser, potentially unifying desktop and web puzzle implementations.
