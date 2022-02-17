#include "game/component.hpp"
#include "game/entity.hpp"

Entity* SpaceshipWeaponCmpt::ShootBullet(const Point& dir) {
    if (bulletAmount == 0) return nullptr;
    if (bulletAmount != InfBullet) {
        bulletAmount --;
    }
    Entity* bullet = CreateBullet(owner->Get<GroupCmpt>()->groupIdx, damage, owner, maxSpeed);
    bullet->Use<MotionCmpt>()->speed = Normalize(dir) * shootSpeed;
    bullet->Use<MoveCmpt>()->position = owner->Get<MoveCmpt>()->position;
    return bullet;
}

Entity* SpaceshipWeaponCmpt::ShootMissile(const Point& dir, Entity* target) {
    if (bulletAmount == 0) return nullptr;
    if (bulletAmount != InfBullet) {
        bulletAmount --;
    }
    Entity* bullet = CreateMissile(owner->Get<GroupCmpt>()->groupIdx, damage, owner, maxSpeed, target);
    if (target) {
        bullet->Use<BulletCmpt>()->rotation = Degrees(std::acos(Dot(dir, Normalize(target->Get<MoveCmpt>()->position - owner->Get<MoveCmpt>()->position))));
    }
    bullet->Use<MotionCmpt>()->speed = Normalize(dir) * shootSpeed;
    bullet->Use<MoveCmpt>()->position = owner->Get<MoveCmpt>()->position;
    Sounds["missile"]->Play();
    return bullet;
}
