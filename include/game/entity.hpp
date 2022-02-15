#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/component.hpp"
#include "game/global.hpp"

Entity* CreateFreightShip(int group);
Entity* CreateFightShip(int group);
Entity* CreateBullet(int group, int damage, Entity* owner, float maxSpeed);
Entity* CreateMissile(int group, int damage, Entity* owner, float maxSpeed, Entity* target);
