#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/quick_list.hpp"
#include "game/init_info.hpp"

extern Context ECSContext;
extern SystemManager SystemMgr;
extern Unique<TileSheet> GameTileSheet;
extern std::unordered_map<std::string, Unique<Sound>> Sounds;

extern QuickList<Entity*> Bullets;
extern QuickList<Entity*> Entities;

extern Entity* PlayerSpaceship;

extern std::array<QuickList<Entity*>, 4> Groups;

extern GameInitInfo InitInfo;

void LoadResources();
Point MapGlobal2PlayerCoord(const Point& pos);
Point MapPlayerCoord2Global(const Point& pos);
