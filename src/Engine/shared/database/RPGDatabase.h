#pragma once
#include <string>
#include <vector>
#include <memory>
#include "src/Utility/ArrayList.h"
#include "src/Utility/AssetData.h"
#include "src/Engine/map/MapData.h"
#include "src/Engine/rpg/event/SkillData.h"
#include "src/Utility/BobString.h"

namespace OKGame {

    struct ActorData {
        int id = -1;
        std::string name;
        int classId = 0;
        int initialLevel = 1;
        std::string faceName;
        std::string characterName;
        std::string description;

        std::string& initFromString(std::string& t) {
            auto parseField = [&](const std::string& key, std::string& out) {
                size_t pos = t.find(key + ":`") ;
                if (pos == std::string::npos) return;
                size_t start = t.find("`", pos) + 1;
                size_t end = t.find("`", start);
                if (start != std::string::npos && end != std::string::npos) {
                    out = t.substr(start, end - start);
                }
            };

            auto parseIntField = [&](const std::string& key, int& out) {
                std::string s;
                parseField(key, s);
                if (!s.empty()) {
                    try { out = std::stoi(s); } catch (...) {}
                }
            };

            parseIntField("id", id);
            parseField("name", name);
            parseIntField("classId", classId);
            parseIntField("initialLevel", initialLevel);
            parseField("faceName", faceName);
            parseField("characterName", characterName);
            parseField("description", description);

            size_t next = t.find("},");
            if (next != std::string::npos) t = t.substr(next + 2);
            return t;
        }
    };

    struct ItemData {
        int id = -1;
        std::string name;
        std::string description;
        int price = 0;
        bool consumable = false;
        int itypeId = 0;

        std::string& initFromString(std::string& t) {
            auto parseField = [&](const std::string& key, std::string& out) {
                size_t pos = t.find(key + ":`") ;
                if (pos == std::string::npos) return;
                size_t start = t.find("`", pos) + 1;
                size_t end = t.find("`", start);
                if (start != std::string::npos && end != std::string::npos) {
                    out = t.substr(start, end - start);
                }
            };

            auto parseIntField = [&](const std::string& key, int& out) {
                std::string s;
                parseField(key, s);
                if (!s.empty()) {
                    try { out = std::stoi(s); } catch (...) {}
                }
            };

            parseIntField("id", id);
            parseField("name", name);
            parseField("description", description);
            parseIntField("price", price);

            std::string cons;
            parseField("consumable", cons);
            consumable = BobBoolean::parseBoolean(cons);

            parseIntField("itypeId", itypeId);

            size_t next = t.find("},");
            if (next != std::string::npos) t = t.substr(next + 2);
            return t;
        }
    };

    struct EnemyData {
        int id = -1;
        std::string name;
        int mhp = 0;
        int atk = 0;
        int def = 0;
        int gold = 0;

        std::string& initFromString(std::string& t) {
            auto parseField = [&](const std::string& key, std::string& out) {
                size_t pos = t.find(key + ":`") ;
                if (pos == std::string::npos) return;
                size_t start = t.find("`", pos) + 1;
                size_t end = t.find("`", start);
                if (start != std::string::npos && end != std::string::npos) {
                    out = t.substr(start, end - start);
                }
            };

            auto parseIntField = [&](const std::string& key, int& out) {
                std::string s;
                parseField(key, s);
                if (!s.empty()) {
                    try { out = std::stoi(s); } catch (...) {}
                }
            };

            parseIntField("id", id);
            parseField("name", name);
            parseIntField("mhp", mhp);
            parseIntField("atk", atk);
            parseIntField("def", def);
            parseIntField("gold", gold);

            size_t next = t.find("},");
            if (next != std::string::npos) t = t.substr(next + 2);
            return t;
        }
    };

    class RPGDatabase {
    public:
        ArrayList<std::shared_ptr<ActorData>> actors;
        ArrayList<std::shared_ptr<SkillData>> skills;
        ArrayList<std::shared_ptr<ItemData>> items;
        ArrayList<std::shared_ptr<EnemyData>> enemies;
        ArrayList<std::shared_ptr<MapData>> maps;
        ArrayList<std::shared_ptr<AssetData>> assets;

        std::string& initFromString(std::string& t) {
            auto parseList = [&](const std::string& key, auto& list, auto creator) {
                size_t pos = t.find(key + ":{");
                if (pos == std::string::npos) return;
                t = t.substr(pos + key.length() + 2);
                while (!String::startsWith(t, "}")) {
                    auto data = creator();
                    t = data->initFromString(t);
                    list.add(data);
                }
                size_t endPos = t.find("}");
                if (endPos != std::string::npos) t = t.substr(endPos + 1);
                if (String::startsWith(t, ",")) t = t.substr(1);
            };

            parseList("actors", actors, [](){ return std::make_shared<ActorData>(); });
            parseList("skills", skills, [](){ return std::make_shared<SkillData>(); });
            parseList("items", items, [](){ return std::make_shared<ItemData>(); });
            parseList("enemies", enemies, [](){ return std::make_shared<EnemyData>(); });
            parseList("maps", maps, [](){ return std::make_shared<MapData>(); });
            parseList("assets", assets, [](){ return std::make_shared<AssetData>(); });

            return t;
        }
    };

}
