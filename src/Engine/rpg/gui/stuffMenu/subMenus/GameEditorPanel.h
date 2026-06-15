#pragma once
#include "src/Engine/rpg/gui/stuffMenu/SubPanel.h"

namespace OKGame {
    class GameEditorPanel : public SubPanel {
    public:
        GameEditorPanel() : SubPanel() {}
        virtual void init() override;
        virtual void update() override;
        virtual void render() override;
    };
}
