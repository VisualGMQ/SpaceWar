#include "game/entity.hpp"
#include "game/constants.hpp"

Entity* CreateFreightShip() {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, FreightShipMaxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(0, 0));
    auto weapon = ECSContext.CreateComponent<SpaceshipWeaponCmpt>("BULLET",
                                                                  SpaceshipWeaponCmpt::FreeRotation,
                                                                  BulletCmpt::Bullet,
                                                                  entity,
                                                                  LazerDamage,
                                                                  LazerShooterSpeed,
                                                                  LazerShooterMaxSpeed,
                                                                  LazerShooterCooldown);
    entity->Add<CollisionCmpt>(Size{16, 16});
    entity->Add<LifeCmpt>(FreightLife);
    entity->Add<FreightShipCmpt>(weapon);
    return entity;
}

Entity* CreateFightShip() {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, FightShipMaxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(1, 0));

    auto weapon1 = ECSContext.CreateComponent<SpaceshipWeaponCmpt>("BULLET",
                                                                   SpaceshipWeaponCmpt::Orientation,
                                                                   BulletCmpt::Bullet,
                                                                   entity,
                                                                   LazerDamage,
                                                                   LazerShooterSpeed,
                                                                   LazerShooterMaxSpeed,
                                                                   LazerShooterCooldown);
    auto weapon2 = ECSContext.CreateComponent<SpaceshipWeaponCmpt>("MISSILE",
                                                                   SpaceshipWeaponCmpt::Orientation,
                                                                   BulletCmpt::Missile,
                                                                   entity,
                                                                   LazerDamage,
                                                                   LazerShooterSpeed,
                                                                   LazerShooterMaxSpeed,
                                                                   LazerShooterCooldown);

    entity->Add<CollisionCmpt>(Size{16, 16});
    entity->Add<LifeCmpt>(FreightLife);
    entity->Add<FightShipCmpt>(weapon1, weapon2);
    return entity;
}

Entity* CreateBullet(int damage, Entity* owner, float maxSpeed) {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, maxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(0, 1));
    entity->Add<BulletCmpt>(BulletCmpt::Bullet, damage, owner);
    entity->Add<CollisionCmpt>(Size{8, 8});
    return entity;
}

Entity* CreateMissile(int damage, Entity* owner, float maxSpeed, Entity* target) {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, maxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(2, 1));
    entity->Add<BulletCmpt>(BulletCmpt::Missile, damage, owner, target);
    entity->Add<CollisionCmpt>(Size{10, 10});
    return entity;
}
