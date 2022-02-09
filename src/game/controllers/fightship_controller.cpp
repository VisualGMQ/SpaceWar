#include "game/controllers/fightship_controller.hpp"
#include "tinyengine/event.hpp"

FightShipController::FightShipController(Entity* entity)
    : entity_(entity) {}

void FightShipController::Update(float dt) {
    const float spd = 100;
    auto motionCmpt = entity_->Use<MotionCmpt>();
    float& rotation = entity_->Use<FightShipCmpt>()->degree;
    if (IsKeyPressing(GLFW_KEY_A)) {
        rotation += 2;
    }
    if (IsKeyPressing(GLFW_KEY_D)) {
        rotation -= 2;
    }
    if (IsKeyPressing(GLFW_KEY_S)) {
        motionCmpt->acceleration = Rotate(Point{0, spd}, -rotation);
    }
    if (IsKeyPressing(GLFW_KEY_W)) {
        motionCmpt->acceleration = Rotate(Point{0, -spd}, -rotation);
    }

    motionCmpt->speed = Rotate(Point{0, -1} * Len(motionCmpt->speed),
                               -rotation);

    auto fightShip = entity_->Use<FightShipCmpt>();
    auto weapon1 = fightShip->weapon1,
         weapon2 = fightShip->weapon2;
    auto moveCmpt = entity_->Get<MoveCmpt>();

    if (IsLeftPressing()) {
        weaponShoot(weapon1, *moveCmpt);
    }
    if (IsRightPressing()) {
        weaponShoot(weapon2, *moveCmpt);
    }
}

void FightShipController::weaponShoot(SpaceshipWeaponCmpt* weapon, const MoveCmpt& move) {
    if (!weapon) return;
    Point dir;
    if (weapon->type == SpaceshipWeaponCmpt::Orientation) {
        dir = Rotate(Point{0, -1}, -entity_->Get<FightShipCmpt>()->degree);
    } else {
        dir = GetMousePosition() - entity_->Get<MoveCmpt>()->position;
    }

    if (weapon->bulletType == BulletCmpt::Bullet) {
        Shoot(*weapon, dir);
    } else {
        Entity* target = nullptr;
        for (auto& entity : Entities) {
            if (entity != entity_ &&
                    IsPointInRect(MapPlayerCoord2Global(GetMousePosition()), entity->Get<CollisionCmpt>()->rect)) {
                target = entity;
                break;
            }
        }
        Shoot(*weapon, dir, target);
    }
}
