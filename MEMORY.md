# Memory: okgame (C++)

## Architectural Observations
- **Engine Evolution:** The engine transitioned from legacy C to Java, and is now being ported to Modern C++ (SDL3) with `std::shared_ptr` management.
- **Monolithic State:** `GameType` acts as the master configuration object for all puzzle mechanics.
- **Networking:** Utilizes Poco WebSockets for high-frequency synchronization with a Node.js backend.
- **UI System:** Uses Gwen (Gwen::Controls) for native C++ menus, while the Java version has migrated to LibGDX Scene2D.

## Codebase Traits
- **Shared Pointer Convention:** Pervasive use of `shared_ptr<T>` for memory safety.
- **Sync Suffix:** Thread-safe methods often carry the `_S` suffix.
- **Submodule Heavy:** Relies on 89+ submodules for audio, video, and utility functions.

## Design Preferences
- **Parity First:** Implementation should prioritize matching the behavior of the Java reference client.
- **Modern Standards:** Favor C++17/20 features and OpenGL 3.3+ Core profile.
