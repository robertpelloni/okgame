# DEPLOY: Build, Environment & Deployment Guide

This guide outlines setup, dependency prerequisites, build workflows, and deployment procedures for the native C++ `okgame` (`bobsgame`) engine.

---

## 1. System Requirements & Toolchains

### Linux (Ubuntu 22.04+ / Debian 12+)
```bash
sudo apt-get update && sudo apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    libxcursor-dev \
    libpulse-dev \
    libxtst-dev \
    libasound2-dev \
    libxi-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxss-dev \
    libwayland-dev \
    libxkbcommon-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libboost-all-dev \
    libpoco-dev
```

### Windows (Visual Studio 2022 / 2019)
- **Visual Studio Build Tools:** C++ Desktop Development workload.
- **CMake:** Version 3.20 or newer.
- **Boost:** Pre-built Boost binaries (configured via `setup_boost.bat` or vcpkg).
- **Poco:** Built via CMake or vendored DLLs in repository root.

### macOS (macOS 12+ / Apple Silicon & Intel)
- Xcode Command Line Tools: `xcode-select --install`
- Dependencies via Homebrew: `brew install cmake ninja poco boost`

---

## 2. Submodule Initialization
Ensure all vendored submodules and visualizer preset packs are retrieved:
```bash
git submodule update --init --recursive
```

---

## 3. CMake Build Instructions

### Configuring & Building on Linux
```bash
# Create build directory
mkdir -p build && cd build

# Configure with CMake (Release mode)
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=17

# Build target
cmake --build . --config Release -j$(nproc)
```

### Running on Linux
Launch using the runtime environment wrapper:
```bash
./linux/bobsgame.sh
```

---

## 4. Distribution Packaging
- **Linux:** Run `linux/prepare_for_launch.sh` to bundle runtime `.so` dependencies into a local `./libs` directory and set appropriate execute permissions on the `bobsgame` binary.
- **Windows:** Run `_make distro.bat` to package executables, necessary runtime DLLs (`SDL2.dll`, `PocoFoundation.dll`, etc.), assets, and presets into the distribution archive.
