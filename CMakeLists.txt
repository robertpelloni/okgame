set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 3.5)
project(bobsgame)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 -fpermissive")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${bobsgame_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_SKIP_INSTALL_RULES ON CACHE BOOL "Skip third-party install/export rules for local validation builds" FORCE)



#find_file(SDL2_INCLUDE_DIR NAME SDL.h HINTS SDL2)
#find_library(SDL2_LIBRARY NAME SDL2)

#find_package(OpenGL)
#find_package(SDL2)
#find_package(SDL2_image)
#find_package(SDL2_mixer)
#find_package(SDL2_ttf)
#find_package(SDL2_net)
#find_package(Boost)

add_subdirectory(lib/SDL)
set(ZLIB_INSTALL OFF CACHE BOOL "Disable zlib install/export generation for local okgame builds" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "Disable AVIF support for local okgame builds" FORCE)
set(SDLIMAGE_AVIF_SAVE OFF CACHE BOOL "Disable AVIF save support for local okgame builds" FORCE)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG OFF CACHE BOOL "Prefer module mode so vendored SDL_image zlib resolves cleanly" FORCE)
add_subdirectory(lib/SDL_image)
set(BUILD_PROGRAMS OFF CACHE BOOL "Disable FLAC/mpg123 tool builds for local okgame validation" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "Disable FLAC examples for local okgame validation" FORCE)
set(BUILD_DOCS OFF CACHE BOOL "Disable FLAC docs for local okgame validation" FORCE)
set(INSTALL_MANPAGES OFF CACHE BOOL "Disable FLAC manpage installation for local okgame validation" FORCE)
set(INSTALL_PKGCONFIG_MODULES OFF CACHE BOOL "Disable FLAC pkg-config install for local okgame validation" FORCE)
set(INSTALL_CMAKE_CONFIG_MODULE OFF CACHE BOOL "Disable FLAC CMake package install for local okgame validation" FORCE)
set(INSTALL_DOCS OFF CACHE BOOL "Disable ogg doc installation for local okgame validation" FORCE)
set(INSTALL_PKG_CONFIG_MODULE OFF CACHE BOOL "Disable ogg pkg-config install for local okgame validation" FORCE)
set(INSTALL_CMAKE_PACKAGE_MODULE OFF CACHE BOOL "Disable ogg CMake package install for local okgame validation" FORCE)
set(SDLMIXER_OPUS OFF CACHE BOOL "Disable Opus support for local okgame builds" FORCE)
add_subdirectory(lib/SDL_mixer)
add_subdirectory(lib/SDL_ttf)
add_subdirectory(lib/SDL_net)
set(POCO_MINIMAL_BUILD ON CACHE BOOL "Build only the Poco components needed by okgame" FORCE)
set(ENABLE_FOUNDATION ON CACHE BOOL "Enable Poco Foundation" FORCE)
set(ENABLE_JSON ON CACHE BOOL "Enable Poco JSON" FORCE)
set(ENABLE_NET ON CACHE BOOL "Enable Poco Net" FORCE)
set(ENABLE_UTIL ON CACHE BOOL "Enable Poco Util" FORCE)
set(ENABLE_XML OFF CACHE BOOL "Disable optional Poco XML for local okgame builds" FORCE)
set(ENABLE_NETSSL OFF CACHE BOOL "Disable optional Poco NetSSL for local okgame builds" FORCE)
set(ENABLE_CRYPTO OFF CACHE BOOL "Disable optional Poco Crypto for local okgame builds" FORCE)
set(ENABLE_JWT OFF CACHE BOOL "Disable optional Poco JWT for local okgame builds" FORCE)
add_subdirectory(lib/poco)
add_subdirectory(lib/GWEN-master/gwen)
add_subdirectory(lib/boost)

#find_library(OPENGL REQUIRED GL)
#find_library(SDL2 REQUIRED sdl2)
#find_library(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
#find_library(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
#find_library(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

#include_directories(
#        ${OPENGL_INCLUDE_DIR}
#        ${SDL2_INCLUDE_DIR}
#        ${SDL2_IMAGE_INCLUDE_DIR}
#        ${SDL2_MIXER_INCLUDE_DIR}
#        ${SDL2_TTF_INCLUDE_DIR}
#        ${SDL2_NET_INCLUDE_DIR}
#        ${bobsgame_SOURCE_DIR}/lib
#        ${bobsgame_SOURCE_DIR}/lib/poco/Foundation/include
#        ${bobsgame_SOURCE_DIR}/lib/poco/JSON/include
#        ${bobsgame_SOURCE_DIR}/lib/poco/Net/include
#        ${bobsgame_SOURCE_DIR}/lib/poco/Util/include
#        ${bobsgame_SOURCE_DIR}/lib/poco/XML/include
#        ${bobsgame_SOURCE_DIR}/lib/poco/Zip/include
#        ${bobsgame_SOURCE_DIR}/lib/miniz-master
#        ${bobsgame_SOURCE_DIR}/lib/minilzo-2.09
#        ${bobsgame_SOURCE_DIR}/lib/GWEN/gwen/include
#        ${bobsgame_SOURCE_DIR}/lib/GWEN-master/gwen/include
#        ${bobsgame_SOURCE_DIR}/lib/projectm/src
#        ${bobsgame_SOURCE_DIR}/lib/libretro-common/include
#        #${bobsgame_SOURCE_DIR}/lib/boost_1_62_0
#        ${Boost_INCLUDE_DIR}
#        ${bobsgame_SOURCE_DIR}/lib/boost
#        ${bobsgame_SOURCE_DIR}
#
#)

set(BOBSGAME_INCLUDE_DIRS
        ${OPENGL_INCLUDE_DIR}
        ${bobsgame_SOURCE_DIR}/lib/SDL/include
        ${bobsgame_SOURCE_DIR}/lib/SDL_image/include
        ${bobsgame_SOURCE_DIR}/lib/SDL_mixer/include
        ${bobsgame_SOURCE_DIR}/lib/SDL_ttf/include
        ${bobsgame_SOURCE_DIR}/lib/SDL_net/include
        ${bobsgame_SOURCE_DIR}/lib/poco/Foundation/include
        ${bobsgame_SOURCE_DIR}/lib/poco/JSON/include
        ${bobsgame_SOURCE_DIR}/lib/poco/Net/include
        ${bobsgame_SOURCE_DIR}/lib/poco/Util/include
        ${bobsgame_SOURCE_DIR}/lib/poco/XML/include
        ${bobsgame_SOURCE_DIR}/lib/poco/Zip/include
        ${bobsgame_SOURCE_DIR}/lib/GWEN-master/gwen/include
        ${bobsgame_SOURCE_DIR}/lib/boost
        ${bobsgame_SOURCE_DIR}/lib/CTPL
        ${bobsgame_SOURCE_DIR}/lib/steam/public
        ${bobsgame_SOURCE_DIR}/lib/CLove/src/3rdparty/lua
        ${bobsgame_SOURCE_DIR}/lib
        ${bobsgame_SOURCE_DIR}
)

# Steamworks Libs
if(WIN32)
    set(STEAM_LIB_PATH ${bobsgame_SOURCE_DIR}/lib/steam/redistributable_bin/win64)
    link_directories(${STEAM_LIB_PATH})
    set(STEAM_LIBS steam_api64)
elseif(LINUX)
    set(STEAM_LIB_PATH ${bobsgame_SOURCE_DIR}/lib/steam/redistributable_bin/linux64)
    link_directories(${STEAM_LIB_PATH})
    set(STEAM_LIBS steam_api)
endif()

#add_definitions(-DBOOST_ALL_NO_LIB=1)# -DBOOST_ALL_DYN_LINK -DBOOST_LOG_DYN_LINK)
add_definitions(-DBOOST_LIB_DIAGNOSTIC=1 -DNOMINMAX -DHAVE_STEAMWORKS=1 -DHAVE_LUA=1 -DLUA_ANSI)

SET (CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN/libs/:$$ORIGIN/libs/'" )

SET (CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN/libs:$$ORIGIN/libs/'" )


set(SOURCE_FILES
        #   Resource.h
        stdafx.cpp
        stdafx.h
        bobtypes.h
        #    targetver.h
        #lib/glew-2.0.0/include/GL/eglew.h
        lib/GWEN/gwen/include/GL/glew.h
        lib/GWEN/gwen/Renderers/OpenGL/glew.c
        lib/HQ2X/HQ2X.cpp
        lib/HQ2X/HQ2X.h
        lib/Snippets/DG_misc.h
        lib/SDL/include/SDL3/SDL_platform.h
        lib/Snippets/SDL_stbimage.h
        lib/stb/stb_image.h
        lib/stb/deprecated/stb_image_resize.h
        lib/stb/stb_image_write.h
        lib/stb/stb_truetype.h
        lib/stb/stb_vorbis.c
        #lib/minilzo-2.09/minilzo.c
        lib/GWEN-master/gwen/src/Input/gwen_input_sdl2.cpp
        lib/md5-c/md5.c
        lib/md5-c/md5.h
        lib/lz4-java/src/lz4/lib/lz4.c
        lib/lz4-java/src/lz4/lib/lz4.h
        lib/lz4-java/src/lz4/lib/lz4frame.c
        lib/lz4-java/src/lz4/lib/lz4frame.h
        lib/lz4-java/src/lz4/lib/lz4frame_static.h
        lib/lz4-java/src/lz4/lib/lz4hc.c
        lib/lz4-java/src/lz4/lib/lz4hc.h
        lib/lz4-java/src/lz4/lib/xxhash.c
        lib/lz4-java/src/lz4/lib/xxhash.h
        lib/miniz/miniz.c
    src/Engine/cinematics/CinematicsManager.cpp
    src/Engine/cinematics/CinematicsManager.h
    src/Engine/cinematics/Letterbox.cpp
    src/Engine/cinematics/Letterbox.h
    src/Engine/cinematics/ScreenOverlay.cpp
    src/Engine/cinematics/ScreenOverlay.h
    src/Engine/entity/Cameraman.cpp
    src/Engine/entity/Cameraman.h
    src/Engine/entity/Character.cpp
    src/Engine/entity/Character.h
    src/Engine/entity/Entity.cpp
    src/Engine/entity/Entity.h
    src/Engine/entity/PathFinder.cpp
    src/Engine/entity/PathFinder.h
    src/Engine/entity/RandomCharacter.cpp
    src/Engine/entity/RandomCharacter.h
    src/Engine/entity/ScreenSprite.cpp
    src/Engine/entity/ScreenSprite.h
    src/Engine/entity/Sprite.cpp
    src/Engine/entity/Sprite.h
    src/Engine/entity/SpriteAnimationSequence.cpp
    src/Engine/entity/SpriteAnimationSequence.h
    src/Engine/entity/SpriteData.cpp
    src/Engine/entity/SpriteData.h
    src/Engine/entity/SpriteManager.cpp
    src/Engine/entity/SpriteManager.h
    src/Engine/map/Area.cpp
    src/Engine/map/Area.h
    src/Engine/map/AreaData.cpp
    src/Engine/map/AreaData.h
    src/Engine/map/Door.cpp
    src/Engine/map/Door.h
    src/Engine/map/DoorData.cpp
    src/Engine/map/DoorData.h
    src/Engine/map/EntityData.cpp
    src/Engine/map/EntityData.h
    src/Engine/map/Light.cpp
    src/Engine/map/Light.h
    src/Engine/map/LightData.cpp
    src/Engine/map/LightData.h
    src/Engine/map/Map.cpp
    src/Engine/map/Map.h
    src/Engine/map/MapData.cpp
    src/Engine/map/MapData.h
    src/Engine/map/MapManager.cpp
    src/Engine/map/MapManager.h
    src/Engine/map/MapState.cpp
    src/Engine/map/MapState.h
    src/Engine/map/MapStateData.cpp
    src/Engine/map/MapStateData.h
    src/Engine/map/WarpArea.cpp
    src/Engine/map/WarpArea.h
    src/Engine/nd/ndmenu/wheelitem/NDMenuInfoPanel.cpp
    src/Engine/nd/ndmenu/wheelitem/NDMenuInfoPanel.h
    src/Engine/nd/ndmenu/wheelitem/NDMenuMovie.cpp
    src/Engine/nd/ndmenu/wheelitem/NDMenuMovie.h
    src/Engine/nd/ndmenu/wheelitem/NDMenuWheelItem.cpp
    src/Engine/nd/ndmenu/wheelitem/NDMenuWheelItem.h
    src/Engine/nd/ndmenu/NDMenu.cpp
    src/Engine/nd/ndmenu/NDMenu.h
    src/Engine/nd/ndmenu/NDMenuBackground.cpp
    src/Engine/nd/ndmenu/NDMenuBackground.h
    src/Engine/nd/ndmenu/NDMenuWheel.cpp
    src/Engine/nd/ndmenu/NDMenuWheel.h
    src/Engine/nd/ping/Ping.cpp
    src/Engine/nd/ping/Ping.h
    src/Engine/nd/ping/PingBackground.cpp
    src/Engine/nd/ping/PingBackground.h
    src/Engine/nd/ping/PingBall.cpp
    src/Engine/nd/ping/PingBall.h
    src/Engine/nd/ping/PingPaddle.cpp
    src/Engine/nd/ping/PingPaddle.h
    src/Engine/nd/ramio/Ramio.cpp
    src/Engine/nd/ramio/Ramio.h
    src/Engine/nd/ramio/RamioBackground.cpp
    src/Engine/nd/ramio/RamioBackground.h
    src/Engine/nd/ramio/RamioBlock.cpp
    src/Engine/nd/ramio/RamioBlock.h
    src/Engine/nd/ramio/RamioBoba.cpp
    src/Engine/nd/ramio/RamioBoba.h
    src/Engine/nd/ramio/RamioBrickBlock.cpp
    src/Engine/nd/ramio/RamioBrickBlock.h
    src/Engine/nd/ramio/RamioGuy.cpp
    src/Engine/nd/ramio/RamioGuy.h
    src/Engine/nd/ramio/RamioMoneyBlock.cpp
    src/Engine/nd/ramio/RamioMoneyBlock.h
    src/Engine/nd/GameDataLoader.cpp
    src/Engine/nd/GameDataLoader.h
    src/Engine/nd/LibretroGame.cpp
    src/Engine/nd/LibretroGame.h
    src/Engine/nd/ND.cpp
    src/Engine/nd/ND.h
    src/Engine/nd/NDGameEngine.cpp
    src/Engine/nd/NDGameEngine.h
    src/Engine/network/BobNet.cpp
    src/Engine/network/BobNet.h
    src/Engine/network/NetworkManager.cpp
    src/Engine/network/NetworkManager.h
    src/Engine/network/GameSave.cpp
    src/Engine/network/GameSave.h
    src/Engine/network/ServerObject.cpp
    src/Engine/network/ServerObject.h
    src/Engine/network/TCPServerConnection.cpp
    src/Engine/network/TCPServerConnection.h
    src/Engine/network/UDPPeerConnection.cpp
    src/Engine/network/UDPPeerConnection.h
    src/Engine/rpg/event/ActionManager.cpp
    src/Engine/rpg/event/ActionManager.h
    src/Engine/rpg/event/Dialogue.cpp
    src/Engine/rpg/event/Dialogue.h
    src/Engine/rpg/event/DialogueData.cpp
    src/Engine/rpg/event/DialogueData.h
    src/Engine/rpg/event/Event.cpp
    src/Engine/rpg/event/Event.h
    src/Engine/rpg/event/EventCommand.cpp
    src/Engine/rpg/event/EventCommand.h
    src/Engine/rpg/event/EventData.cpp
    src/Engine/rpg/event/EventData.h
    src/Engine/rpg/event/EventManager.cpp
    src/Engine/rpg/event/EventManager.h
    src/Engine/rpg/event/EventParameter.cpp
    src/Engine/rpg/event/EventParameter.h
    src/Engine/rpg/event/Flag.cpp
    src/Engine/rpg/event/Flag.h
    src/Engine/rpg/event/FlagData.cpp
    src/Engine/rpg/event/FlagData.h
    src/Engine/rpg/event/GameString.cpp
    src/Engine/rpg/event/GameString.h
    src/Engine/rpg/event/GameStringData.cpp
    src/Engine/rpg/event/GameStringData.h
    src/Engine/rpg/event/Skill.cpp
    src/Engine/rpg/event/Skill.h
    src/Engine/rpg/event/SkillData.cpp
    src/Engine/rpg/event/SkillData.h
    src/Engine/rpg/gui/gameStore/GameItem.cpp
    src/Engine/rpg/gui/gameStore/GameItem.h
    src/Engine/rpg/gui/gameStore/GameStore.cpp
    src/Engine/rpg/gui/gameStore/GameStore.h
    src/Engine/rpg/gui/statusbar/buttons/GameStoreButton.cpp
    src/Engine/rpg/gui/statusbar/buttons/GameStoreButton.h
    src/Engine/rpg/gui/statusbar/buttons/NDButton.cpp
    src/Engine/rpg/gui/statusbar/buttons/NDButton.h
    src/Engine/rpg/gui/statusbar/buttons/StatusBarButton.cpp
    src/Engine/rpg/gui/statusbar/buttons/StatusBarButton.h
    src/Engine/rpg/gui/statusbar/buttons/StuffButton.cpp
    src/Engine/rpg/gui/statusbar/buttons/StuffButton.h
    src/Engine/rpg/gui/statusbar/captions/ClockCaption.cpp
    src/Engine/rpg/gui/statusbar/captions/ClockCaption.h
    src/Engine/rpg/gui/statusbar/captions/DayCaption.cpp
    src/Engine/rpg/gui/statusbar/captions/DayCaption.h
    src/Engine/rpg/gui/statusbar/captions/MoneyCaption.cpp
    src/Engine/rpg/gui/statusbar/captions/MoneyCaption.h
    src/Engine/rpg/gui/statusbar/captions/StatusBarCaption.cpp
    src/Engine/rpg/gui/statusbar/captions/StatusBarCaption.h
    src/Engine/rpg/gui/statusbar/notification/Notification.cpp
    src/Engine/rpg/gui/statusbar/notification/Notification.h
    src/Engine/rpg/gui/statusbar/NotificationManager.cpp
    src/Engine/rpg/gui/statusbar/NotificationManager.h
    src/Engine/rpg/gui/statusbar/StatusBar.cpp
    src/Engine/rpg/gui/statusbar/StatusBar.h
    src/Engine/rpg/gui/stuffMenu/subMenus/ControlsPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/ControlsPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/DebugInfoPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/DebugInfoPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/FriendsPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/FriendsPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/ItemsPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/ItemsPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/LogsPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/LogsPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/MessagesPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/MessagesPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/SettingsPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/SettingsPanel.h
    src/Engine/rpg/gui/stuffMenu/subMenus/StatusPanel.cpp
    src/Engine/rpg/gui/stuffMenu/subMenus/StatusPanel.h
    src/Engine/rpg/gui/stuffMenu/StuffMenu.cpp
    src/Engine/rpg/gui/stuffMenu/StuffMenu.h
    src/Engine/rpg/gui/stuffMenu/SubPanel.cpp
    src/Engine/rpg/gui/stuffMenu/SubPanel.h
    src/Engine/rpg/gui/CountryCodes.cpp
    src/Engine/rpg/gui/CountryCodes.h
    src/Engine/rpg/gui/GameChallengeNotificationPanel.cpp
    src/Engine/rpg/gui/GameChallengeNotificationPanel.h
    src/Engine/rpg/gui/GUIManager.cpp
    src/Engine/rpg/gui/GUIManager.h
    src/Engine/rpg/gui/MenuPanel.cpp
    src/Engine/rpg/gui/MenuPanel.h
    src/Engine/rpg/gui/PlayerEditMenu.cpp
    src/Engine/rpg/gui/PlayerEditMenu.h
    src/Engine/rpg/gui/GameSelectorMenuPanel.cpp
    src/Engine/rpg/gui/GameSelectorMenuPanel.h
    src/Engine/rpg/gui/LobbyMenuPanel.cpp
    src/Engine/rpg/gui/LobbyMenuPanel.h
    src/Engine/rpg/BGClientEngine.h
    src/Engine/rpg/Clock.cpp
    src/Engine/rpg/Clock.h
    src/Engine/rpg/EasingTest.cpp
    src/Engine/rpg/EasingTest.h
    src/Engine/rpg/FriendCharacter.cpp
    src/Engine/rpg/FriendCharacter.h
    src/Engine/rpg/FriendManager.cpp
    src/Engine/rpg/FriendManager.h
    src/Engine/rpg/Item.cpp
    src/Engine/rpg/Item.h
    src/Engine/rpg/Player.cpp
    src/Engine/rpg/Player.h
    src/Engine/rpg/Wallet.cpp
    src/Engine/rpg/Wallet.h
    src/Engine/stadium/BobsGameStadium.cpp
    src/Engine/stadium/BobsGameStadium.h
    src/Engine/stadium/StadiumScreen.cpp
    src/Engine/stadium/StadiumScreen.h
    src/Engine/state/CreateNewAccountState.cpp
    src/Engine/state/CreateNewAccountState.h
    src/Engine/state/GlowTileBackgroundMenuPanel.cpp
    src/Engine/state/GlowTileBackgroundMenuPanel.h
    src/Engine/state/KeyboardMenuPanel.cpp
    src/Engine/state/KeyboardMenuPanel.h
    src/Engine/state/LegalMenuPanel.cpp
    src/Engine/state/LegalMenuPanel.h
    src/Engine/state/LoggedOutState.cpp
    src/Engine/state/LoggedOutState.h
    src/Engine/state/LogoState.cpp
    src/Engine/state/LogoState.h
    src/Engine/state/LoginState.cpp
    src/Engine/state/LoginState.h
    src/Engine/state/ServersHaveShutDownState.cpp
    src/Engine/state/ServersHaveShutDownState.h
    #src/Engine/state/State.cpp
    #src/Engine/state/State.h
    src/Engine/state/StateManager.cpp
    src/Engine/state/StateManager.h
    src/Engine/state/TitleScreenState.cpp
    src/Engine/state/TitleScreenState.h
    src/Engine/state/YouWillBeNotifiedState.cpp
    src/Engine/state/YouWillBeNotifiedState.h
    src/Engine/text/TextManager.cpp
    src/Engine/text/TextManager.h
    src/Engine/text/TextWindow.cpp
    src/Engine/text/TextWindow.h
    src/Engine/Engine.cpp
    src/Engine/Engine.h
    src/Engine/EnginePart.cpp
    src/Engine/EnginePart.h
    src/Engine/MiniGameEngine.cpp
    src/Engine/MiniGameEngine.h
    src/Puzzle/Block.cpp
    src/Puzzle/Block.h
    src/Puzzle/BobsGame.cpp
    src/Puzzle/BobsGame.h
    src/Puzzle/GameTestMenu.cpp
    src/Puzzle/GameTestMenu.h
    src/Puzzle/BobsGameMenus.cpp
    src/Puzzle/BobsGameNetwork.cpp
    src/Puzzle/CustomGameEditor.h
    src/Puzzle/CustomGameEditor.cpp
    src/Puzzle/GlobalSettings.h
    src/Puzzle/PuzzlePlayer.h
    src/Puzzle/GameSequence.h
    src/Puzzle/GameSequence.cpp
    src/Puzzle/GameSequenceEditor.h
    src/Puzzle/GameSequenceEditor.cpp
    src/Puzzle/GameLogic.cpp
    src/Puzzle/GameLogicChains.cpp
    src/Puzzle/GameLogicGarbage.cpp
    src/Puzzle/GameLogicNetwork.cpp
    src/Puzzle/GameLogicRender.cpp
    src/Puzzle/GameLogic.h
    src/Puzzle/Grid.cpp
    src/Puzzle/Grid.h
    src/Puzzle/OKGame.cpp
    src/Puzzle/OKGame.h
    src/Puzzle/OKGameMenus.cpp
    src/Puzzle/OKGameNetwork.cpp
    src/Engine/stadium/OKGameStadium.cpp
    src/Engine/stadium/OKGameStadium.h
    src/Puzzle/Piece.cpp
    src/Puzzle/Piece.h
    src/Puzzle/GameType.cpp
    src/Puzzle/GameType.h
    src/Puzzle/Room.h
    src/Puzzle/Stats/GameStats.h
    src/Puzzle/Stats/LeaderBoardAndHighScoreBoardEntry.h
    src/Puzzle/Stats/UserStatsForSpecificGameAndDifficulty.h
    src/Utility/audio/AudioManager.cpp
    src/Utility/audio/AudioManager.h
    #src/Utility/audio/Music.cpp
    #src/Utility/audio/Music.h
    #src/Utility/audio/MusicData.cpp
    #src/Utility/audio/MusicData.h
    src/Utility/audio/Sound.cpp
    src/Utility/audio/Sound.h
    src/Utility/audio/AudioFile.cpp
    src/Utility/audio/AudioFile.h
    src/Utility/audio/AudioData.cpp
    src/Utility/audio/AudioData.h
    src/Utility/gl/GLUtils.cpp
    src/Utility/gl/GLUtils.h
    src/Utility/gl/Texture.cpp
    src/Utility/gl/Texture.h
    src/Utility/ArrayList.h
    src/Utility/AssetData.cpp
    src/Utility/AssetData.h
    src/Utility/BobBool.cpp
    src/Utility/BobBool.h
    src/Utility/BobFont.cpp
    src/Utility/BobFont.h
    src/Utility/BobMenu.h
    src/Utility/BobMenu.cpp
    src/Utility/BobMath.cpp
    src/Utility/BobMath.h
    src/Utility/BobString.cpp
    src/Utility/BobString.h
    src/Utility/BufferedImage.cpp
    src/Utility/BufferedImage.h
    src/Utility/Caption.cpp
    src/Utility/Caption.h
    src/Utility/CaptionManager.cpp
    src/Utility/CaptionManager.h
    src/Utility/Color.cpp
    src/Utility/Color.h
    src/Utility/Console.cpp
    src/Utility/Console.h
    src/Utility/ConsoleText.cpp
    src/Utility/ConsoleText.h
    src/Utility/ControlsManager.cpp
    src/Utility/ControlsManager.h
    src/Utility/Easing.cpp
    src/Utility/Easing.h
    src/Utility/FileUtils.cpp
    src/Utility/FileUtils.h
    src/Utility/HashMap.h
    src/Utility/Logger.cpp
    src/Utility/Logger.h
    #src/Utility/RectangularVectors.h
    src/Utility/stringconverter.h
    src/Utility/System.cpp
    src/Utility/System.h
    src/main.cpp
    src/main.h

)



add_library(glew STATIC
    lib/GWEN/gwen/Renderers/OpenGL/glew.c
    lib/GWEN/gwen/include/GL/glew.h
)
target_include_directories(glew PUBLIC lib/GWEN/gwen/include)
target_compile_definitions(glew PUBLIC GLEW_STATIC)

add_library(GLEW::glew ALIAS glew)
add_library(GLEW::glew_s ALIAS glew)
set(STD_FILESYSTEM_EXISTS TRUE CACHE BOOL "" FORCE)
option(ENABLE_PROJECTM "Enable projectM visualizer integration" ON)
set(ENABLE_PROJECTM_AVAILABLE OFF)
if(ENABLE_PROJECTM AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/lib/projectm/vendor/projectm-eval/CMakeLists.txt")
    add_subdirectory(lib/projectm)
    set(ENABLE_PROJECTM_AVAILABLE ON)
else()
    message(WARNING "projectM disabled for this build because lib/projectm/vendor/projectm-eval is unavailable.")
endif()
#add_subdirectory(lib/gambatte-libretro)
#set_target_properties(gambatte_libretro PROPERTIES
#    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cores"
#    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cores"
#)
add_executable(bobsgame ${SOURCE_FILES})
target_include_directories(bobsgame PRIVATE ${BOBSGAME_INCLUDE_DIRS})
target_link_libraries(bobsgame
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        SDL3_ttf::SDL3_ttf
        SDL3_net::SDL3_net
        Poco::Foundation
        Poco::Net
        Poco::JSON
        Poco::Util
        #Poco::XML
        #Poco::Zip
        GWEN_static
        #GWEN_opengl
        Boost::serialization
        ${STEAM_LIBS}
)
if(ENABLE_PROJECTM_AVAILABLE)
    target_link_libraries(bobsgame projectM)
endif()
if(ENABLE_PROJECTM_AVAILABLE)
    target_compile_definitions(bobsgame PRIVATE HAVE_PROJECTM=1)
else()
    target_compile_definitions(bobsgame PRIVATE HAVE_PROJECTM=0)
endif()

# Deploy VERSION.md to the output directory
add_custom_command(
    TARGET bobsgame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/VERSION.md
        $<TARGET_FILE_DIR:bobsgame>/VERSION.md
    COMMENT "Copying VERSION.md to output directory"
)




#add_custom_command(
#        TARGET bobsgame
#        POST_BUILD
#        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/linux/prepare_for_launch.sh"
#        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/linux"
#        COMMENT "Running prepare_for_launch.sh"
#        VERBATIM
#        )
