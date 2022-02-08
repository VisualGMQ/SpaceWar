#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/quick_list.hpp"

extern Context ECSContext;
extern SystemManager SystemMgr;
extern Unique<TileSheet> GameTileSheet;
extern std::unordered_map<std::string, Unique<Sound>> Sounds;

extern QuickList<Entity*> Bullets;

extern QuickList<Entity*> Entities;

void LoadResources();
