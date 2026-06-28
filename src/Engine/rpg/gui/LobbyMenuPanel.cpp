#include "stdafx.h"
#include "LobbyMenuPanel.h"
#include "GUIManager.h"
#include "Puzzle/BobsGame.h"
#include "Engine/nd/ND.h"
#include "main.h"

namespace {
    const std::vector<std::string> kLobbyGameModes = { "marathon", "sprint", "ultra" };

    std::string formatGameModeLabel(const std::string& gameMode)
    {
        if (gameMode == "sprint") return "Sprint (40 Lines)";
        if (gameMode == "ultra") return "Ultra (3 Min)";
        return "Marathon";
    }
}

LobbyMenuPanel::LobbyMenuPanel()
{
}

LobbyMenuPanel::~LobbyMenuPanel()
{
}

void LobbyMenuPanel::init()
{
}

void LobbyMenuPanel::onRoomListReceived(const std::vector<LobbyRoom>& rooms)
{
    std::lock_guard<std::mutex> lock(m_roomMutex);
    m_rooms = rooms;
    m_roomsUpdated = true;
}

void LobbyMenuPanel::onChatMessageReceived(Poco::Dynamic::Var data)
{
    try {
        Poco::JSON::Object::Ptr obj = data.extract<Poco::JSON::Object::Ptr>();
        std::string name = obj->getValue<std::string>("name");
        std::string msg = obj->getValue<std::string>("message");
        std::lock_guard<std::mutex> lock(m_chatMutex);
        m_chatMessages.push_back(name + ": " + msg);
        if (m_chatMessages.size() > 5) m_chatMessages.erase(m_chatMessages.begin());
        m_chatUpdated = true;
    } catch (...) {}
}

std::string LobbyMenuPanel::getSelectedGameMode() const
{
    if (m_gameModeIndex < 0 || m_gameModeIndex >= (int)kLobbyGameModes.size())return kLobbyGameModes[0];
    return kLobbyGameModes[m_gameModeIndex];
}

std::string LobbyMenuPanel::getPasswordStars() const
{
    return std::string(m_roomPassword.size(), '*');
}

std::string LobbyMenuPanel::getRoomSummary(const LobbyRoom& room) const
{
    std::string lockStr = room.hasPassword ? " [Private]" : "";
    return room.name + lockStr + " (" + std::to_string(room.players) + "/" + std::to_string(room.maxPlayers) + ") - " + formatGameModeLabel(room.gameMode) + " Lv." + std::to_string(room.startLevel);
}

void LobbyMenuPanel::rebuildMenu()
{
    if (menu == nullptr)return;

    menu->clear();
    menu->addInfo(m_statusMessage);
    menu->add("Room Name: " + (m_roomName.size() > 0 ? m_roomName : "New Room"), "Room Name");
    menu->add("Password: " + getPasswordStars(), "Password");
    menu->add(std::string("Private Room: ") + (m_privateRoom ? "Yes" : "No"), "Private Room");
    menu->add("Game Mode: " + formatGameModeLabel(getSelectedGameMode()), "Game Mode");
    menu->add("Start Level: " + std::to_string(m_startLevel), "Start Level");
    menu->add("Create Room");
    menu->add("Send Message");

    if (!m_chatMessages.empty()) {
        menu->addInfo("--- Chat ---");
        for (const auto& msg : m_chatMessages) {
            menu->addInfo(msg);
        }
    }

    menu->addInfo("--- Rooms ---");
    for (const auto& room : m_rooms) {
        menu->add(getRoomSummary(room), room.id);
    }
    menu->add("Back");

    if (menu->cursorPosition >= menu->getAmountOfMenuItems())menu->cursorPosition = menu->getAmountOfMenuItems() - 1;
    if (menu->cursorPosition < 0)menu->cursorPosition = 0;
}

void LobbyMenuPanel::startNetworkGame(long long seed, const std::string& gameMode, int startLevel)
{
    BobsGame* bobsGame = new BobsGame();
    bobsGame->setNetworkGame(true);
    bobsGame->setPendingNetworkStart(seed, startLevel, gameMode);
    bobsGame->init();
    getND()->setGame(bobsGame);
    getND()->setActivated(true);
    setActivated(false);
}

void LobbyMenuPanel::update()
{
    MenuPanel::update();

    if (getIsActivated() == true)
    {
        if (getIsScrollingDown() == false)
        {
            if (menu == nullptr)
            {
                menu = new BobMenu(getEngine(), "Multiplayer Lobby");
                rebuildMenu();
            }

            Main::networkManager->setRoomListCallback([this](const std::vector<LobbyRoom>& rooms) {
                this->onRoomListReceived(rooms);
            });
            Main::networkManager->on("chatMessage", [this](Poco::Dynamic::Var data) {
                this->onChatMessageReceived(data);
            });
            Main::networkManager->on("roomCreated", [this](Poco::Dynamic::Var data) {
                try {
                    Poco::JSON::Object::Ptr obj = data.extract<Poco::JSON::Object::Ptr>();
                    Main::networkManager->joinRoom(obj->getValue<std::string>("id"), m_roomPassword);
                }
                catch (...) {
                    m_statusMessage = "Room created, but auto-join failed.";
                    m_roomsUpdated = true;
                }
            });
            Main::networkManager->on("joinedRoom", [this](Poco::Dynamic::Var data) {
                try {
                    Poco::JSON::Object::Ptr obj = data.extract<Poco::JSON::Object::Ptr>();
                    m_joinedRoom = true;
                    m_joinedRoomName = obj->getValue<std::string>("name");
                    m_statusMessage = "Waiting in " + m_joinedRoomName + " for the match to start...";
                    m_roomsUpdated = true;
                }
                catch (...) {}
            });
            Main::networkManager->on("gameStart", [this](Poco::Dynamic::Var data) {
                try {
                    Poco::JSON::Object::Ptr obj = data.extract<Poco::JSON::Object::Ptr>();
                    long long seed = obj->getValue<long long>("seed");
                    int startLevel = obj->has("startLevel") ? obj->getValue<int>("startLevel") : 1;
                    std::string gameMode = obj->has("gameMode") ? obj->getValue<std::string>("gameMode") : "marathon";
                    this->startNetworkGame(seed, gameMode, startLevel);
                }
                catch (...) {}
            });
            Main::networkManager->on("error", [this](Poco::Dynamic::Var data) {
                try {
                    m_statusMessage = "Server error: " + data.convert<std::string>();
                }
                catch (...) {
                    m_statusMessage = "Server error.";
                }
                m_roomsUpdated = true;
            });

            if (m_connected == false)
            {
                Main::networkManager->connect("http://localhost:6065");
                Main::networkManager->listRooms();
                m_lastRefreshTime = System::getTicks();
                m_connected = true;
            }

            if (System::getTicks() - m_lastRefreshTime > 5000) {
                Main::networkManager->listRooms();
                m_lastRefreshTime = System::getTicks();
            }

            {
                std::lock_guard<std::mutex> lock(m_roomMutex);
                std::lock_guard<std::mutex> lockChat(m_chatMutex);
                if (m_roomsUpdated || m_chatUpdated) {
                    rebuildMenu();
                    m_roomsUpdated = false;
                    m_chatUpdated = false;
                }
            }

            if (getIsScrolledUp())
            {
                int mx = getControlsManager()->getMouseX();
                int my = getControlsManager()->getMouseY();

                if (mx != m_lastMouseX || my != m_lastMouseY)
                {
                    if (m_textStarted) { Main::StopTextInput(); m_textStarted = false; }
                    m_lastMouseX = mx;
                    m_lastMouseY = my;
                }

                if (getControlsManager()->miniGame_UP_Pressed()) { menu->up(); if (m_textStarted) { Main::StopTextInput(); m_textStarted = false; } }
                if (getControlsManager()->miniGame_DOWN_Pressed() || getControlsManager()->key_TAB_Pressed()) { menu->down(); if (m_textStarted) { Main::StopTextInput(); m_textStarted = false; } }

                if (menu->isSelectedID("Room Name"))
                {
                    if (!m_textStarted) { Main::StartTextInput(); getControlsManager()->text = m_roomName; m_textStarted = true; }
                    m_roomName = getControlsManager()->text;
                    menu->getMenuItemByID("Room Name")->setText("Room Name: " + (m_roomName.size() > 0 ? m_roomName : "New Room"));
                }
                else if (menu->isSelectedID("Password"))
                {
                    if (!m_textStarted) { Main::StartTextInput(); getControlsManager()->text = m_roomPassword; m_textStarted = true; }
                    m_roomPassword = getControlsManager()->text;
                    menu->getMenuItemByID("Password")->setText("Password: " + getPasswordStars());
                }
                else
                {
                    if (m_textStarted) { Main::StopTextInput(); m_textStarted = false; }
                }

                bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();
                bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
                bool leftPressed = getControlsManager()->miniGame_LEFT_Pressed();
                bool rightPressed = getControlsManager()->miniGame_RIGHT_Pressed();

                if (confirm || clicked || leftPressed || rightPressed)
                {
                    if (menu->isSelectedID("Private Room", clicked, mx, my))
                    {
                        if (leftPressed || rightPressed || confirm || clicked)
                        {
                            m_privateRoom = !m_privateRoom;
                            if (m_privateRoom == false)m_roomPassword = "";
                            menu->getMenuItemByID("Private Room")->setText(std::string("Private Room: ") + (m_privateRoom ? "Yes" : "No"));
                            menu->getMenuItemByID("Password")->setText("Password: " + getPasswordStars());
                        }
                    }
                    else if (menu->isSelectedID("Game Mode", clicked, mx, my))
                    {
                        if (leftPressed)m_gameModeIndex--;
                        else m_gameModeIndex++;

                        if (m_gameModeIndex < 0)m_gameModeIndex = (int)kLobbyGameModes.size() - 1;
                        if (m_gameModeIndex >= (int)kLobbyGameModes.size())m_gameModeIndex = 0;
                        menu->getMenuItemByID("Game Mode")->setText("Game Mode: " + formatGameModeLabel(getSelectedGameMode()));
                    }
                    else if (menu->isSelectedID("Start Level", clicked, mx, my))
                    {
                        if (leftPressed)m_startLevel--;
                        else m_startLevel++;

                        if (m_startLevel < 1)m_startLevel = 20;
                        if (m_startLevel > 20)m_startLevel = 1;
                        menu->getMenuItemByID("Start Level")->setText("Start Level: " + std::to_string(m_startLevel));
                    }
                }

                if (confirm || clicked)
                {
                    if (menu->isSelectedID("Create Room", clicked, mx, my))
                    {
                        std::string roomName = m_roomName.size() > 0 ? m_roomName : "New Room";
                        Main::networkManager->createRoom(roomName, m_privateRoom, m_roomPassword, getSelectedGameMode(), m_startLevel);
                        m_statusMessage = "Creating room " + roomName + "...";
                        m_roomsUpdated = true;
                    }
                    else if (menu->isSelectedID("Send Message", clicked, mx, my))
                    {
                        std::string playerName = "C++Player";
                        Main::networkManager->sendChat("Hello from C++!", playerName);
                    }
                    else if (menu->isSelectedID("Back", clicked, mx, my))
                    {
                        setActivated(false);
                    }
                    else {
                        string id = menu->getSelectedMenuItem()->id;
                        if (id != "" && id != "Create Room" && id != "Back" && id != "Send Message" && id != "Room Name" && id != "Password" && id != "Private Room" && id != "Game Mode" && id != "Start Level") {
                            Main::networkManager->joinRoom(id, m_roomPassword);
                            m_statusMessage = "Joining room...";
                            m_roomsUpdated = true;
                        }
                    }
                }

                if (getControlsManager()->miniGame_CANCEL_Pressed())
                {
                    setActivated(false);
                }
            }
        }
    }

    if (getIsActivated() == false && getIsScrollingDown() == false)
    {
        if (m_textStarted) { Main::StopTextInput(); m_textStarted = false; }
        getControlsManager()->text = "";
        m_joinedRoom = false;
        m_joinedRoomName = "";
        m_statusMessage = "Edit the room options, create a room, or join one from the list below.";

        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
    }
}

void LobbyMenuPanel::render()
{
    MenuPanel::render();
}
