#pragma once
#include "../System.h"
#include "../components/CombatComponent.h"
#include <iostream>
#include <vector>

namespace OKGame {
    enum class CombatState {
        IDLE,
        PLAYER_TURN,
        ENEMY_TURN,
        VICTORY,
        DEFEAT
    };

    class CombatSystem : public System {
    private:
        CombatState state = CombatState::IDLE;
        float turnTimer = 0;
        const float turnDuration = 1.0f;

    public:
        void update(float dt, std::map<EntityId, std::map<std::string, std::shared_ptr<Component>>>& entities) override {
            std::shared_ptr<CombatComponent> player = nullptr;
            std::vector<std::shared_ptr<CombatComponent>> enemies;

            for (auto& [id, components] : entities) {
                if (components.count("Combat")) {
                    auto combat = std::static_pointer_cast<CombatComponent>(components["Combat"]);
                    if (combat->isDead) continue;

                    if (combat->isPlayer) player = combat;
                    else enemies.push_back(combat);
                }
            }

            if (!player || enemies.empty()) {
                state = CombatState::IDLE;
                return;
            }

            if (state == CombatState::IDLE) {
                state = CombatState::PLAYER_TURN;
                turnTimer = 0;
            }

            turnTimer += dt;
            if (turnTimer >= turnDuration) {
                if (state == CombatState::PLAYER_TURN) {
                    executePlayerAttack(player, enemies[0]);
                    if (enemies[0]->isDead) {
                        bool allDead = true;
                        for (auto& e : enemies) if (!e->isDead) allDead = false;
                        if (allDead) state = CombatState::VICTORY;
                        else state = CombatState::ENEMY_TURN;
                    } else {
                        state = CombatState::ENEMY_TURN;
                    }
                } else if (state == CombatState::ENEMY_TURN) {
                    for (auto& enemy : enemies) {
                        if (!enemy->isDead) executeEnemyAttack(enemy, player);
                    }
                    if (player->isDead) state = CombatState::DEFEAT;
                    else state = CombatState::PLAYER_TURN;
                }
                turnTimer = 0;
            }
        }

    private:
        void executePlayerAttack(std::shared_ptr<CombatComponent> attacker, std::shared_ptr<CombatComponent> target) {
            float damage = attacker->atk - target->def;
            if (damage < 1) damage = 1;
            target->hp -= damage;
            if (target->hp <= 0) {
                target->hp = 0;
                target->isDead = true;
                std::cout << "[Combat] Enemy defeated!" << std::endl;
            }
        }

        void executeEnemyAttack(std::shared_ptr<CombatComponent> attacker, std::shared_ptr<CombatComponent> target) {
            float damage = attacker->atk - target->def;
            if (damage < 1) damage = 1;
            target->hp -= damage;
            if (target->hp <= 0) {
                target->hp = 0;
                target->isDead = true;
                std::cout << "[Combat] Player defeated!" << std::endl;
            }
        }
    };
}
