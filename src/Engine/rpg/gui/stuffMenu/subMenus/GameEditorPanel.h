#pragma once
#include "src/Engine/rpg/gui/stuffMenu/SubPanel.h"
#include "src/Utility/BobMenu.h"

namespace OKGame {
    class GameEditorPanel : public SubPanel {
    public:
        BobMenu* menu = nullptr;

        GameEditorPanel() : SubPanel() {}
        virtual ~GameEditorPanel();
        virtual void init() override;
        virtual void update() override;
        virtual void render() override;
    };
}
