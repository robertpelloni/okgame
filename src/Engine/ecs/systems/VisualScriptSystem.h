#pragma once
#include "../System.h"
#include "../components/EventSheetComponent.h"
#include <iostream>
#include <variant>

namespace OKGame {
    class VisualScriptSystem : public System {
    public:
        void update(float dt, std::map<EntityId, std::map<std::string, std::shared_ptr<Component>>>& entities) override {
            for (auto& [id, components] : entities) {
                if (components.count("EventSheet")) {
                    auto esComp = std::static_pointer_cast<EventSheetComponent>(components["EventSheet"]);
                    for (auto& sheet : esComp->eventSheets) {
                        for (auto& block : sheet.blocks) {
                            processBlock(block, esComp);
                        }
                    }
                }
            }
        }

    private:
        void processBlock(const EventBlock& block, std::shared_ptr<EventSheetComponent> comp) {
            if (checkConditions(block, comp)) {
                runActions(block, comp);
                for (const auto& subBlock : block.subEvents) {
                    processBlock(subBlock, comp);
                }
            }
        }

        bool checkConditions(const EventBlock& block, std::shared_ptr<EventSheetComponent> comp) {
            for (const auto& cond : block.conditions) {
                if (cond.type == "Always") continue;
                if (cond.type == "VariableEquals") {
                    if (cond.params.count("name")) {
                        std::string varName = std::any_cast<std::string>(cond.params.at("name"));
                        if (comp->variables.count(varName)) {
                             // logic for variable comparison placeholder
                        } else return false;
                    }
                }
                // Add more logic for specific condition types
            }
            return true;
        }

        void runActions(const EventBlock& block, std::shared_ptr<EventSheetComponent> comp) {
            for (const auto& action : block.actions) {
                if (action.type == "Log") {
                    std::cout << "[ECS Event] Log Action" << std::endl;
                } else if (action.type == "SetVariable") {
                    if (action.params.count("name") && action.params.count("value")) {
                        std::string varName = std::any_cast<std::string>(action.params.at("name"));
                        comp->variables[varName] = action.params.at("value");
                    }
                }
                // Add more action implementations
            }
        }
    };
}
