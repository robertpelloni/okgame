#pragma once
#include "src/Engine/rpg/gui/stuffMenu/SubPanel.h"
#include "src/Utility/BobMenu.h"

namespace OKGame {
    class RPGEditorControl;

    class EditorsPanel : public SubPanel {
    public:
        BobMenu* menu = nullptr;
        RPGEditorControl* rpgEditor = nullptr;

        EditorsPanel() : SubPanel() {}
        virtual ~EditorsPanel();
        virtual void init() override;
        virtual void update() override;
        virtual void render() override;
    };
}
