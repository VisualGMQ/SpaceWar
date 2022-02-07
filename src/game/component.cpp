#include "game/component.hpp"
#include "game/entity.hpp"

Entity* SpaceshipWeaponCmpt::ShootBullet(const Point& dir) {
    Entity* bullet = CreateBullet(damage, owner, maxSpeed);
    bullet->Use<MotionCmpt>()->speed = Normalize(dir) * shootSpeed;
    bullet->Use<MoveCmpt>()->position = owner->Get<MoveCmpt>()->position;
    return bullet;
}
