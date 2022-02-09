#pragma once

#include "tinyengine/libmath.hpp"

constexpr float FreightShipMaxSpeed = 100;
constexpr float FightShipMaxSpeed = 250;
constexpr int FreightLife = 10;
constexpr float LazerDamage = 2;
constexpr float LazerShooterSpeed = 500;
constexpr float LazerShooterMaxSpeed = 1000;
constexpr float LazerShooterCooldown = 0.3;
constexpr float MissileRotateDegree = 150;

constexpr Size GameWindowSize = {1024, 720};

constexpr Rect BulletRefreshArea{-100, -100, 1124, 820};
constexpr Rect SpaceshipRefreshArea{-1024 * 3, -720 * 3, 1024 * 7, 720 * 7};
