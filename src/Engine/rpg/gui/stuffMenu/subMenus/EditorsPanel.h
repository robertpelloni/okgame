#pragma once
#include "src/Engine/rpg/gui/stuffMenu/SubPanel.h"

namespace OKGame {
    class EditorsPanel : public SubPanel {
    public:
        EditorsPanel() : SubPanel() {}
        virtual void init() override;
        virtual void update() override;
        virtual void render() override;
    };
}
