#pragma once
#include "../System.h"
#include "../components/EventSheetComponent.h"
#include "../components/TransformComponent.h"
#include <iostream>
#include <variant>
#include <any>

namespace OKGame {
    class VisualScriptSystem : public System {
    public:
        void update(float dt, std::map<EntityId, std::map<std::string, std::shared_ptr<Component>>>& entities) override {
            for (auto& [id, components] : entities) {
                if (components.count("EventSheet")) {
                    auto esComp = std::static_pointer_cast<EventSheetComponent>(components["EventSheet"]);
                    for (auto& sheet : esComp->eventSheets) {
                        for (auto& block : sheet.blocks) {
                            processBlock(block, esComp, components, dt);
                        }
                    }
                }
            }
        }

    private:
        void processBlock(const EventBlock& block, std::shared_ptr<EventSheetComponent> comp, std::map<std::string, std::shared_ptr<Component>>& entityComponents, float dt) {
            if (checkConditions(block, comp, entityComponents)) {
                runActions(block, comp, entityComponents, dt);
                for (const auto& subBlock : block.subEvents) {
                    processBlock(subBlock, comp, entityComponents, dt);
                }
            }
        }

        bool checkConditions(const EventBlock& block, std::shared_ptr<EventSheetComponent> comp, std::map<std::string, std::shared_ptr<Component>>& entityComponents) {
            for (const auto& cond : block.conditions) {
                if (cond.type == "Always") continue;

                if (cond.type == "VariableEquals") {
                    if (cond.params.count("name") && cond.params.count("value")) {
                        std::string varName = std::any_cast<std::string>(cond.params.at("name"));
                        if (comp->variables.count(varName)) {
                             auto currentVal = comp->variables.at(varName);
                             auto targetVal = cond.params.at("value");
                             // Basic comparison for string/int
                             if (currentVal.type() == targetVal.type()) {
                                 if (currentVal.type() == typeid(int)) {
                                     if (std::any_cast<int>(currentVal) != std::any_cast<int>(targetVal)) return false;
                                 } else if (currentVal.type() == typeid(std::string)) {
                                     if (std::any_cast<std::string>(currentVal) != std::any_cast<std::string>(targetVal)) return false;
                                 } else if (currentVal.type() == typeid(bool)) {
                                     if (std::any_cast<bool>(currentVal) != std::any_cast<bool>(targetVal)) return false;
                                 }
                             } else return false;
                        } else return false;
                    }
                }

                if (cond.type == "HasComponent") {
                    if (cond.params.count("name")) {
                        std::string compName = std::any_cast<std::string>(cond.params.at("name"));
                        if (entityComponents.find(compName) == entityComponents.end()) return false;
                    }
                }
            }
            return true;
        }

        void runActions(const EventBlock& block, std::shared_ptr<EventSheetComponent> comp, std::map<std::string, std::shared_ptr<Component>>& entityComponents, float dt) {
            for (const auto& action : block.actions) {
                if (action.type == "Log") {
                    if (action.params.count("message")) {
                         std::cout << "[ECS Event] Log: " << std::any_cast<std::string>(action.params.at("message")) << std::endl;
                    } else {
                         std::cout << "[ECS Event] Log Action" << std::endl;
                    }
                } else if (action.type == "SetVariable") {
                    if (action.params.count("name") && action.params.count("value")) {
                        std::string varName = std::any_cast<std::string>(action.params.at("name"));
                        comp->variables[varName] = action.params.at("value");
                    }
                } else if (action.type == "Move") {
                    if (entityComponents.count("Transform")) {
                        auto transform = std::static_pointer_cast<TransformComponent>(entityComponents["Transform"]);
                        float moveX = 0, moveY = 0;
                        if (action.params.count("x")) moveX = std::any_cast<float>(action.params.at("x"));
                        if (action.params.count("y")) moveY = std::any_cast<float>(action.params.at("y"));
                        transform->x += moveX * dt;
                        transform->y += moveY * dt;
                    }
                }
            }
        }
    };
}
