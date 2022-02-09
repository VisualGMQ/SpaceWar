#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/component.hpp"
#include "game/global.hpp"

Entity* CreateFreightShip();
Entity* CreateFightShip();
Entity* CreateBullet(int damage, Entity* owner, float maxSpeed);
Entity* CreateMissile(int damage, Entity* owner, float maxSpeed, Entity* target);
