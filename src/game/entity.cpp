#include "game/entity.hpp"

Entity* CreateFreightShip() {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, FreightMaxSpeed);
    entity->Add<RenderCmpt>(TileSheets[TileSheetName]->GetTile(0, 0));
    entity->Add<SpaceshipWeaponCmpt>(SpaceshipWeaponCmpt::Orientation,
                                     entity,
                                     LazerDamage,
                                     LazerShooterSpeed,
                                     LazerShooterMaxSpeed,
                                     LazerShooterCooldown);
    return entity;
}

Entity* CreateBullet(int damage, Entity* owner, float maxSpeed) {
    Entity* entity = ECSContext.CreateEntity();
    entity->Add<MoveCmpt>(Point{0, 0});
    entity->Add<MotionCmpt>(Point{0, 0}, maxSpeed);
    entity->Add<RenderCmpt>(TileSheets[TileSheetName]->GetTile(0, 1));
    entity->Add<BulletCmpt>(damage, owner);
    return entity;
}
