#pragma once

#include "tinyengine/libmath.hpp"

constexpr float FightShipMaxSpeed = 400;
constexpr int   FightShipLife = 10;
constexpr float FightShipRotationDegree = 6;
constexpr float FightShipAccelration = 200;

constexpr float FreightShipMaxSpeed = 100;
constexpr int   FreightShipLife = 15;
constexpr float FreightShipAccelerate = 100;

constexpr float LazerDamage = 3.4;
constexpr float LazerShooterSpeed = 800;
constexpr float LazerShooterMaxSpeed = 2000;
constexpr float LazerShooterCooldown = 0.15;

constexpr float MissileRotateDegree = 150;

constexpr float CoreMaxHp = 100;
constexpr int CoreEnergyProductDuration = 2;
constexpr int CoreEnergyProductAmount = 1;

constexpr Size GameWindowSize = {1024, 720};

constexpr Rect BulletRefreshArea{-100, -100, 1124, 820};
constexpr int BlockSize = 16;

constexpr int PlayerGroup = 0;
constexpr int Enemy1Group = 1;
constexpr int Enemy2Group = 2;
constexpr int Enemy3Group = 3;

constexpr float EntityRenderSize = 20;
constexpr float EntityCollisionSize = 16;
