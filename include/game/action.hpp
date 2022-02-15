#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/component.hpp"
#include "game/entity.hpp"

void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir);
void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir, Entity* target);
void MoveLeft(MotionCmpt& motion);
void MoveRight(MotionCmpt& motion);
void MoveUp(MotionCmpt& motion);
void MoveDown(MotionCmpt& motion);
void SpeedUp(MotionCmpt& motion, FightShipCmpt& ship);
void SpeedDown(MotionCmpt& motion, FightShipCmpt& ship);
void TurnLeft(FightShipCmpt& motion);
void TurnRight(FightShipCmpt& motion);
