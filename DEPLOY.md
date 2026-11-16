# Deployment: okgame (C++)

## Environment Setup
### Prerequisites
- **CMake:** 3.15 or higher.
- **Compiler:** MSVC 2022 (Windows), GCC 11+ (Linux), or Clang (macOS).
- **Dependencies:** Most are included as submodules in `lib/`. Ensure `git submodule update --init --recursive` is run.

## Build Instructions
1. `mkdir build && cd build`
2. `cmake ..`
3. `cmake --build . --config Release`

## Runtime Requirements
- **Data Folder:** The `data/` and `resources/` directories must be present in the execution path.
- **Steamworks:** Requires `steam_api64.dll` (Windows) or `libsteam_api.so` (Linux) if `HAVE_STEAMWORKS=1` is defined.

## Cross-Platform Notes
- **Windows:** Utilize `_build.bat` for quick builds.
- **Linux:** Ensure SDL3 development headers are available if not using vendored submodules.
