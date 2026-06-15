#pragma once
#include <string>
#include <vector>
#include <memory>
#include "src/Utility/ArrayList.h"
#include "src/Utility/AssetData.h"
#include "src/Engine/map/MapData.h"
#include "src/Engine/rpg/event/SkillData.h"

namespace OKGame {

    struct ActorData {
        int id;
        std::string name;
        int classId;
        int initialLevel;
        std::string faceName;
        std::string characterName;
        std::string description;
    };

    struct ItemData {
        int id;
        std::string name;
        std::string description;
        int price;
        bool consumable;
        int itypeId;
    };

    struct EnemyData {
        int id;
        std::string name;
        int mhp;
        int atk;
        int def;
        int gold;
    };

    class RPGDatabase {
    public:
        ArrayList<std::shared_ptr<ActorData>> actors;
        ArrayList<std::shared_ptr<SkillData>> skills;
        ArrayList<std::shared_ptr<ItemData>> items;
        ArrayList<std::shared_ptr<EnemyData>> enemies;
        ArrayList<std::shared_ptr<MapData>> maps;
        ArrayList<std::shared_ptr<AssetData>> assets;
    };

}
