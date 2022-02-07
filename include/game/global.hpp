#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/quick_list.hpp"

extern Context ECSContext;
extern SystemManager SystemMgr;
extern std::unordered_map<std::string, Unique<TileSheet>> TileSheets;
extern std::unordered_map<std::string, Unique<Sound>> Sounds;
extern std::string TileSheetName;

extern QuickList<Entity*> Bullets;

using EntityList = std::vector<Entity*>;

extern EntityList Entities;

void LoadResources();
