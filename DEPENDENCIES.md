# Dependencies Mapping: Java to C++

| Java Library | C++ Equivalent | Status |
|--------------|----------------|--------|
| LWJGL (GLFW/OpenGL) | SDL3 / OpenGL 3.3 Core | Integrated |
| LWJGL (OpenAL) | SDL3_mixer | Integrated |
| LWJGL (STB) | stb (submodule) | Integrated |
| LibGDX (Scene2D) | Gwen (Gwen::Controls) | Integrated |
| Gson | Poco::JSON | Integrated |
| Netty | Poco::Net | Integrated |
| Socket.io-client | Poco::Net::WebSocket | Integrated |
| SLF4J / Logback | Custom Logger | Integrated |
| Commons-IO / FileUtils | FileUtils / std::filesystem | Integrated |
| Apache Commons Compress | Poco::Zip / miniz | Integrated |
| MySQL Connector/J | Poco::Data::MySQL (Pending) | Needed for Server |
| LZ4 | lz4 (submodule) | Integrated |
| JInput | SDL3 Gamepad API | Integrated |
| BCrypt | libbcrypt (Pending) | Needed for Auth |

## Source Mapping

| Java Package | C++ Directory |
|--------------|---------------|
| `com.bobsgame.client.engine` | `src/Engine` |
| `com.bobsgame.puzzle` | `src/Puzzle` |
| `com.bobsgame.shared` | `src/Engine/shared` (partially) |
| `com.bobsgame.client.engine.ecs` | `src/Engine/ecs` |
| `com.bobsgame.client.engine.map` | `src/Engine/map` |
| `com.bobsgame.client.engine.entity` | `src/Engine/entity` |
| `com.bobsgame.client.engine.game` | `src/Engine/rpg` |
