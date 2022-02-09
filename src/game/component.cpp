#include "game/component.hpp"
#include "game/entity.hpp"

Entity* SpaceshipWeaponCmpt::ShootBullet(const Point& dir) {
    Entity* bullet = CreateBullet(damage, owner, maxSpeed);
    bullet->Use<MotionCmpt>()->speed = Normalize(dir) * shootSpeed;
    bullet->Use<MoveCmpt>()->position = owner->Get<MoveCmpt>()->position;
    return bullet;
}

Entity* SpaceshipWeaponCmpt::ShootMissile(const Point& dir, Entity* target) {
    Entity* bullet = CreateMissile(damage, owner, maxSpeed, target);
    if (target) {
    bullet->Use<BulletCmpt>()->rotation = Degrees(std::acos(Dot(dir, Normalize(target->Get<MoveCmpt>()->position - owner->Get<MoveCmpt>()->position))));
    }
    bullet->Use<MotionCmpt>()->speed = Normalize(dir) * shootSpeed;
    bullet->Use<MoveCmpt>()->position = owner->Get<MoveCmpt>()->position;
    return bullet;
}
