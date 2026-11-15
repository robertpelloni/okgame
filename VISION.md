# VISION: bob's game / OKGame (C++ Engine)

## 1. Executive Summary & Core Identity
`bob's game` (OKGame) is an expansive, cross-platform multimedia platform blending a hyper-responsive competitive puzzle engine, nostalgic 2D RPG world-building, high-fidelity real-time music visualization (`MilkDrop3` / `projectM`), decentralized in-game virtual economy (`bobcoin`), and unified emulation capabilities via `Libretro`.

The core mission is total cross-platform parity, deterministic puzzle mechanics, user-driven creative flexibility (the Custom Game & Ruleset Editor), and frictionless community play across native desktop (Linux, Windows, macOS), mobile, and web targets.

---

## 2. Foundational Pillars

### A. The Ultimate Competitive Puzzle Engine
- **Cross-Platform Parity:** Pixel-perfect and tick-deterministic puzzle simulation across C++, Java, and TypeScript/Web implementations.
- **Ruleset Flexibility:** Support for classic block dropping modes, cascading color matches, gravity variations, rotation wall-kicks, customizable bag randomizers, hold queues, and complex garbage distribution systems.
- **Deep In-Game Custom Editor:** Players can author custom piece types, multiform block rotations, custom textures, palette palettes, and granular difficulty curves directly inside the client.

### B. High-Fidelity Music Visualization
- **ProjectM & MilkDrop3 Integration:** Deep audio visualization embedded directly into the gameplay rendering pipeline.
- **Audio Feedback Loop:** Dynamic post-mix PCM streaming via SDL3/SDL_mixer feeds frequency and waveform analysis into GPU fragment shaders with seamless preset auto-cycling and manual controls.
- **Atmospheric Immersion:** Seamless visual transitions behind transparent grid boards to elevate puzzle sessions into audiovisual spectacles.

### C. Emulation & Multi-Game Hub (Libretro Frontend)
- **Universal Nostalgia Gateway:** Built-in Libretro core runner allowing players to access and play classic games within the in-game virtual devices ("nD").
- **Modern Quality-of-Life:** Real-time state saving/loading with visual thumbnails, multi-slot persistence, fast-forward, zero-latency rewind buffers, CRT shader emulation (Flat and Curved scanlines), cheat code support, and automatic core association.

### D. Decentralized Economy & Community (`bobcoin`)
- **Frictionless Virtual Economy:** Lightweight in-game currency inspired by privacy and speed, enabling decentralized tournament prize pools, cosmetic rewards, custom skin trading, and community verification.
- **Proof-of-Play & Mining:** Rewarding puzzle mastery, endurance marathon clears, and rhythm interactions with cryptographic token tracking.

---

## 3. Architecture & Engineering Principles

### Modern C++ Standards & Memory Safety
- **Strict Smart Pointer Discipline:** Elimination of raw pointers across core subsystems (`EnginePart`, `Entity`, `Map`, `Audio`, `Network`) in favor of `std::shared_ptr` (`sp<T>`) and `std::weak_ptr` (`wp<T>`) with custom deleters where necessary to prevent cyclic references and leaks.
- **Thread Safety Governance:** Clear delineation of thread-safe boundaries (`_S` suffix conventions, `_Mutex` variable patterns) protecting incoming network packets, audio callback queues, and input event rings.
- **Modern Hardware Abstraction:** Modernized SDL3 audio, joystick, and window event backends targeting Core Profile OpenGL 3.3+ and future Vulkan integration.

---

## 4. User Satisfaction & Intuitive Interface Philosophy
- **Consolidation Over Fragmentation:** High-value controls, network lobbies, visualizer configurations, and audio settings are aggregated into clear, hierarchical, single-page dashboards rather than nested menus.
- **Direct Visual Feedback:** Real-time visual previews for editor changes, interactive tooltips on all configurable toggles, and live log telemetry.
- **Graceful Error Handling & Fallbacks:** Seamless audio driver fallback, offline fallback for network services, and non-destructive configuration persistence.
