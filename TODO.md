# TODO: okgame (C++)

## Immediate Tasks
- [x] **Port RPGDatabase:** Port `com.bobsgame.shared.database.RPGDatabase` from Java to `src/Engine/shared/database/RPGDatabase.h`.
- [x] **Port EditorsPanel:** Implement `EditorsPanel` in C++ Gwen UI to match Java.
- [x] **Port GameEditorPanel:** Implement `GameEditorPanel` in C++ Gwen UI to match Java.
- [x] **Enhance VisualScriptSystem:** Expand condition/action handling in `VisualScriptSystem.h`.
- [x] **Smart Pointer Audit:** Ensure all new RPG engine components use `std::shared_ptr`.
- [ ] **Implement Asset Registry:** Wire `RPGDatabase` to the `GameDataLoader` for automated object instantiation.
- [ ] **Combat System Port:** Port the turn-based combat logic from Java to the C++ ECS.

## Bug Fixes
- [ ] Resolve memory leaks in legacy RPG engine components during map transitions.
- [ ] Fix potential race conditions in `NetworkManager` JSON parsing.
- [ ] Verify `miniz` behavior with large Base64-encoded map chunks.

## Polish
- [x] Sync `CustomGameEditor` with the latest Java/Web preset summary UX.
- [ ] Modernize RPG engine render calls to use SDL3 vertex arrays.
- [ ] Implement tooltips for all `RPGEditorControl` fields.
