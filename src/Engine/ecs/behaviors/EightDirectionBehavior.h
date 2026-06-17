#pragma once
#include "Behavior.h"
#include "../World.h"
#include "../components/TransformComponent.h"
#include "../../Utility/ControlsManager.h"
#include "../../main.h"
#include <cmath>

namespace OKGame {
    class EightDirectionBehavior : public Behavior {
    private:
        World* world;
        float speed = 200.0f;

    public:
        EightDirectionBehavior(World* w) : world(w) {}

        void onInit() override {}

        void onUpdate(float dt) override {
            auto transform = world->getComponent<TransformComponent>(entityId, "Transform");
            if (!transform) return;

            float dx = 0;
            float dy = 0;

            ControlsManager* cm = Main::getControlsManager();
            if (cm) {
                if (cm->BGCLIENT_LEFT_HELD) dx -= 1.0f;
                if (cm->BGCLIENT_RIGHT_HELD) dx += 1.0f;
                if (cm->BGCLIENT_UP_HELD) dy -= 1.0f;
                if (cm->BGCLIENT_DOWN_HELD) dy += 1.0f;
            }

            if (dx != 0 || dy != 0) {
                float mag = std::sqrt(dx * dx + dy * dy);
                transform->x += (dx / mag) * speed * dt;
                transform->y += (dy / mag) * speed * dt;
            }
        }
    };
}
