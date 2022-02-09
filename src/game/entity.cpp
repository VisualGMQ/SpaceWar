#include "game/entity.hpp"
#include "game/constants.hpp"

Entity* CreateFreightShip() {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, FreightShipMaxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(0, 0));
    entity->Add<SpaceshipWeaponCmpt>(SpaceshipWeaponCmpt::FreeRotation,
                                     entity,
                                     LazerDamage,
                                     LazerShooterSpeed,
                                     LazerShooterMaxSpeed,
                                     LazerShooterCooldown);
    entity->Add<CollisionCmpt>(Size{16, 16});
    entity->Add<LifeCmpt>(FreightLife);
    entity->Add<FreightShipCmpt>();
    return entity;
}

Entity* CreateFightShip() {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, FightShipMaxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(1, 0));
    entity->Add<SpaceshipWeaponCmpt>(SpaceshipWeaponCmpt::Orientation,
                                     entity,
                                     LazerDamage,
                                     LazerShooterSpeed,
                                     LazerShooterMaxSpeed,
                                     LazerShooterCooldown);
    entity->Add<CollisionCmpt>(Size{16, 16});
    entity->Add<LifeCmpt>(FreightLife);
    entity->Add<FightShipCmpt>(0);
    return entity;
}

Entity* CreateBullet(int damage, Entity* owner, float maxSpeed) {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, maxSpeed);
    entity->Add<RenderCmpt>(GameTileSheet->GetTile(0, 1));
    entity->Add<BulletCmpt>(damage, owner);
    entity->Add<CollisionCmpt>(Size{8, 8});
    return entity;
}
