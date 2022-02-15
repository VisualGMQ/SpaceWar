#include "game/action.hpp"

void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir) {
    if (weapon.IsCoolDowning()) {
        return;
    }

    Point playerCenterPos = weapon.owner->Get<MoveCmpt>()->position;

    Entity* bullet;
    bullet = weapon.ShootBullet(dir);
    if (bullet) {
        Bullets.Add(bullet);
        weapon.coolDown = weapon.shootDuration;
        Sounds["shoot"]->Play();
    }
}

void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir, Entity* target) {
    if (weapon.IsCoolDowning()) {
        return;
    }

    Point playerCenterPos = weapon.owner->Get<MoveCmpt>()->position;

    Entity* bullet;
    bullet = weapon.ShootMissile(dir, target);
    if (bullet) {
        // FIXME the rotation have some bugs
        bullet->Use<BulletCmpt>()->rotation = Degrees(std::acos(-Normalize(dir).y));
        Bullets.Add(bullet);
        weapon.coolDown = weapon.shootDuration;
        Sounds["shoot"]->Play();
    }
}

void MoveLeft(MotionCmpt& motion) {
    motion.acceleration += Point{-FreightShipAccelerate, 0};
}

void MoveRight(MotionCmpt& motion) {
    motion.acceleration += Point{FreightShipAccelerate, 0};
}

void MoveUp(MotionCmpt& motion) {
    motion.acceleration += Point{0, -FreightShipAccelerate};
}

void MoveDown(MotionCmpt& motion) {
    motion.acceleration += Point{0, FreightShipAccelerate};
}

void SpeedUp(MotionCmpt& motion, FightShipCmpt& ship) {
    motion.acceleration = Rotate(Point{0, FightShipAccelration},
                                 -ship.degree);
}

void SpeedDown(MotionCmpt& motion, FightShipCmpt& ship) {
    motion.acceleration = Rotate(Point{0, -FightShipAccelration},
                                 -ship.degree);
}

void TurnLeft(FightShipCmpt& ship) {
    ship.degree += FightShipRotationDegree;
}

void TurnRight(FightShipCmpt& ship) {
    ship.degree -= FightShipRotationDegree;
}
