# TODO: okgame (C++)

## Immediate Tasks
- [ ] **Port RPGDatabase:** Port `com.bobsgame.shared.database.RPGDatabase` from Java to `src/Engine/shared/database/RPGDatabase.h`.
- [ ] **Port EditorsPanel:** Implement `EditorsPanel` in C++ Gwen UI to match Java.
- [ ] **Port GameEditorPanel:** Implement `GameEditorPanel` in C++ Gwen UI to match Java.
- [ ] **Enhance VisualScriptSystem:** Expand condition/action handling in `VisualScriptSystem.h`.
- [ ] **Smart Pointer Audit:** Ensure all new RPG engine components use `std::shared_ptr`.

## Bug Fixes
- [ ] Resolve memory leaks in legacy RPG engine components during map transitions.
- [ ] Fix potential race conditions in `NetworkManager` JSON parsing.

## Polish
- [ ] Sync `CustomGameEditor` with the latest Java/Web preset summary UX.
- [ ] Modernize RPG engine render calls to use SDL3 vertex arrays.
