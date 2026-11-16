#include "stdafx.h"
#include "EditorsPanel.h"
#include "src/Engine/rpg/gui/RPGEditorControl.h"
#include "src/Utility/ControlsManager.h"
#include "src/Engine/rpg/BGClientEngine.h"
#include "src/Engine/rpg/gui/GUIManager.h"
#include "src/main.h"

namespace OKGame {
    EditorsPanel::~EditorsPanel() {
        if (menu) delete menu;
        if (rpgEditor) {
            rpgEditor->DelayedDelete();
            rpgEditor = nullptr;
        }
    }

    void EditorsPanel::init() {
        SubPanel::init();
    }

    void EditorsPanel::update() {
        SubPanel::update();

        if (getIsActivated()) {
            if (rpgEditor) return;

            if (menu == nullptr) {
                menu = new BobMenu(getEngine(), "Editors");
                menu->add("RPG Editor");
                menu->add("Map Editor");
                menu->add("Sprite Editor");
                menu->add("Puzzle Editor");
            }

            int mx = getControlsManager()->getMouseX();
            int my = getControlsManager()->getMouseY();

            if (getControlsManager()->miniGame_UP_Pressed()) menu->up();
            if (getControlsManager()->miniGame_DOWN_Pressed()) menu->down();

            bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();
            bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

            if (confirm || clicked) {
                if (menu->isSelectedID("RPG Editor", clicked, mx, my)) {
                    if (rpgEditor == nullptr) {
                        rpgEditor = new RPGEditorControl(Main::gwenCanvas);
                        // rpgEditor->setDatabase(...)
                    }
                    rpgEditor->SetVisible(true);
                }
                if (menu->isSelectedID("Puzzle Editor", clicked, mx, my)) {
                    // Logic to open puzzle editor
                }
            }
        } else {
            if (menu) {
                delete menu;
                menu = nullptr;
            }
            if (rpgEditor) {
                rpgEditor->SetVisible(false);
            }
        }
    }

    void EditorsPanel::render() {
        SubPanel::render();
        if (getIsActivated() && menu) {
            menu->render();
        }
    }
}
