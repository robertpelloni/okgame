# bob's game — the C++ puzzle game ("okgame")

The C++ implementation of **bob's game**: a multiplayer puzzle game that is also a puzzle-game *creation system* — players define their own rulesets to recreate existing puzzle games or invent new ones, then play them locally or online with tournament-style features (wall/floor/spin kicks, T-spins, adjustable timing, powerups) applied uniformly across game types.

> **Extreme WIP alpha, developed in the open.** The original README's warning stands: don't bother trying to use it unless you plan on hacking on it to get it working.

## This repo in the bob's game family

- **`okgame` (this repo)** — the C++ engine (CMake + SDL2). Also a submodule of `bg`.
- [`bobsgameweb`](https://github.com/robertpelloni/bobsgameweb) — the TypeScript/PixiJS engine (package name also "okgame"), the most active build; live at bobsgame.com.
- [`bobsgameonlinejava`](https://github.com/robertpelloni/bobsgameonlinejava) — the original Java client/server (2D MMORPG engine).
- [`bg`](https://github.com/robertpelloni/bg) — the umbrella workspace tying all three together, with the porting/consolidation tooling.

## Building

CMake-based; see **`COMPILING.md`** in this repo for the authoritative instructions. The tree carries Visual Studio project files (`ALL_BUILD.vcxproj`, `_build.bat`, `_make distro.bat`) for Windows builds and prebuilt SDL2/Poco DLLs for that platform. Eclipse/CDT metadata (`.cproject`, `.project`) is also checked in.

## License

Public domain / free as in speech, per the project's own declaration — see `LICENSE` in this repo. Do whatever.
