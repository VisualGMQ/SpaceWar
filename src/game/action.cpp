#include "game/action.hpp"

void Shoot(SpaceshipWeaponCmpt& weapon, const Point& dir) {
    if (weapon.IsCoolDowning()) return;

    Point playerCenterPos = weapon.owner->Get<MoveCmpt>()->position;

    auto bullet = weapon.ShootBullet(dir);
    Bullets.Add(bullet);

    weapon.coolDown = weapon.shootDuration;

    Sounds["shoot"]->Play();
}
