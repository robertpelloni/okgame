#include "stdafx.h"
#include "GameEditorPanel.h"
#include "src/Utility/ControlsManager.h"
#include "src/Engine/rpg/BGClientEngine.h"
#include "src/Engine/rpg/gui/GUIManager.h"

namespace OKGame {
    GameEditorPanel::~GameEditorPanel() {
        if (menu) delete menu;
    }

    void GameEditorPanel::init() {
        SubPanel::init();
    }

    void GameEditorPanel::update() {
        SubPanel::update();

        if (getIsActivated()) {
            if (menu == nullptr) {
                menu = new BobMenu(getEngine(), "Game Editor");
                menu->add("New Game");
                menu->add("Load Game");
                menu->add("Save Game");
            }

            int mx = getControlsManager()->getMouseX();
            int my = getControlsManager()->getMouseY();

            if (getControlsManager()->miniGame_UP_Pressed()) menu->up();
            if (getControlsManager()->miniGame_DOWN_Pressed()) menu->down();

            bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();
            bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

            if (confirm || clicked) {
                if (menu->isSelectedID("New Game", clicked, mx, my)) {
                    // Logic to create new game
                }
            }
        } else {
            if (menu) {
                delete menu;
                menu = nullptr;
            }
        }
    }

    void GameEditorPanel::render() {
        SubPanel::render();
        if (getIsActivated() && menu) {
            menu->render();
        }
    }
}
