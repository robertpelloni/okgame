#include "stdafx.h"
#include "src/Engine/nd/GameDataLoader.h"
#include "src/Engine/Engine.h"
#include "src/Engine/entity/SpriteManager.h"
#include "src/Engine/entity/Sprite.h"
#include "src/Engine/entity/SpriteData.h"
#include "src/Engine/map/MapManager.h"
#include "src/Engine/map/Map.h"
#include "src/Engine/map/MapData.h"
#include "src/Utility/FileUtils.h"
#include "src/main.h"

Logger GameDataLoader::log = Logger("GameDataLoader");

GameDataLoader::GameDataLoader(Engine* g) : EnginePart(g)
{
	this->e = g;
	loadGameData();
}

void GameDataLoader::loadGameData()
{
	FileUtils::downloadBigFileToCacheIfNotExist("gameData");

	ArrayList<string>* stringList = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("gameData");
    if (!stringList) {
        log.error("Could not load gameData file");
        return;
    }

	if (stringList->size() > 0)
	{
		for (int i = 0; i < stringList->size(); i++)
		{
			string s = stringList->get(i);

			if (s.length() > 0)
			{
				if (s == "Sprites")
				{
					i++;
                    if (i >= stringList->size()) break;
					s = stringList->get(i);
					while (s.length() > 1)
					{
						if (s.length() > 0)
						{
							size_t colonPos = s.find(":");
                            if (colonPos != string::npos) {
                                s = s.substr(colonPos + 1);
                            }
							string json = FileUtils::unzipBase64StringToString(s);
							sp<SpriteData> data = ms<SpriteData>();
                            data->initFromString(json);

							sp<Sprite> sprite = ms<Sprite>(e->shared_from_this());
							sprite->initializeWithSpriteData(data);

							getSpriteManager()->spriteByIDHashMap.put(sprite->getID(), sprite);
							getSpriteManager()->spriteByNameHashMap.put(sprite->getName(), sprite);

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i);
                            unsigned long len = 0;
                            u8* bytes = FileUtils::unzipBase64StringToByteArray(s, len);
                            if (bytes) {
                                // Logic for indexDataIntArray would go here
                                delete[] bytes;
                            }

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i);
                            // sprite->paletteRGBByteArray = ...

							sprite->loadTextures();

							if (debug) log.debug("Loaded Sprite: " + data->getName());

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i);
						}
                        if (s == "Maps") break;
					}
				}

				if (s == "Maps")
				{
					i++;
                    if (i >= stringList->size()) break;
					s = stringList->get(i);
					while (s.length() > 1)
					{
						if (s.length() > 0)
						{
							size_t colonPos = s.find(":");
                            if (colonPos != string::npos) {
                                s = s.substr(colonPos + 1);
                            }
                            string json = FileUtils::unzipBase64StringToString(s);
							sp<MapData> data = ms<MapData>();
                            data->initFromString(json);

							sp<Map> map = ms<Map>(e->shared_from_this(), data);

							getMapManager()->mapList.add(map);
							getMapManager()->mapByIDHashMap.put(map->getID(), map);
							getMapManager()->mapByNameHashMap.put(map->getName(), map);

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i); // tileData

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i); // paletteData

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i); // mapLayerData

							if (debug) log.debug("Loaded Map: " + data->getName());

							i++;
                            if (i >= stringList->size()) break;
							s = stringList->get(i);
						}
                        if (s == "Sounds" || s == "Music") break;
					}
				}
			}
		}
	}
    delete stringList;
}
