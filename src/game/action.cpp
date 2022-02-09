#include "game/action.hpp"

void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir) {
    if (weapon.IsCoolDowning()) {
        return;
    }

    Point playerCenterPos = weapon.owner->Get<MoveCmpt>()->position;

    Entity* bullet;
    bullet = weapon.ShootBullet(dir);
    Bullets.Add(bullet);

    weapon.coolDown = weapon.shootDuration;

    Sounds["shoot"]->Play();
}

void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir, Entity* target) {
    if (weapon.IsCoolDowning()) {
        return;
    }

    Point playerCenterPos = weapon.owner->Get<MoveCmpt>()->position;

    Entity* bullet;
    bullet = weapon.ShootMissile(dir, target);

    // FIXME the rotation have some bugs
    bullet->Use<BulletCmpt>()->rotation = Degrees(std::acos(-Normalize(dir).y));

    Bullets.Add(bullet);

    weapon.coolDown = weapon.shootDuration;

    Sounds["shoot"]->Play();
}

