#include "game/controllers/fightship_controller.hpp"
#include "tinyengine/event.hpp"

FightShipController::FightShipController(Entity* entity)
    : entity_(entity) {}

void FightShipController::Update(float dt) {
    if (!entity_ || !entity_->IsAlive()) {
        return;
    }

    const float spd = 100;
    auto motionCmpt = entity_->Use<MotionCmpt>();
    auto ship = entity_->Use<FightShipCmpt>();
    if (IsKeyPressing(GLFW_KEY_A)) {
        TurnLeft(*ship);
    }
    if (IsKeyPressing(GLFW_KEY_D)) {
        TurnRight(*ship);
    }
    if (IsKeyPressing(GLFW_KEY_S)) {
        SpeedDown(*motionCmpt, *ship);
    }
    if (IsKeyPressing(GLFW_KEY_W)) {
        SpeedUp(*motionCmpt, *ship);
    }

    motionCmpt->speed = Rotate(Point{0, -1} * Len(motionCmpt->speed),
                               ship->degree);

    auto moveCmpt = entity_->Get<MoveCmpt>();

    if (IsLeftPressing()) {
        if (entity_->Has<FightShipCmpt>()) {
            weaponShoot(entity_->Use<FightShipCmpt>()->weapon1, *moveCmpt);
        } else if (entity_->Has<FreightShipCmpt>()) {
            weaponShoot(entity_->Use<FreightShipCmpt>()->weapon, *moveCmpt);
        }
    }
    if (IsRightPressing()) {
        if (entity_->Has<FightShipCmpt>()) {
            weaponShoot(entity_->Use<FightShipCmpt>()->weapon2, *moveCmpt);
        } else if (entity_->Has<FreightShipCmpt>()) {
            weaponShoot(entity_->Use<FreightShipCmpt>()->weapon, *moveCmpt);
        }
    }
}

void FightShipController::weaponShoot(SpaceshipWeaponCmpt* weapon, const MoveCmpt& move) {
    if (!weapon) return;
    Point dir;
    if (weapon->type == SpaceshipWeaponCmpt::Orientation) {
        dir = Rotate(Point{0, -1}, entity_->Get<FightShipCmpt>()->degree);
    } else {
        dir = GetMousePosition() - GameWindowSize / 2;
    }

    if (weapon->bulletType == BulletCmpt::Bullet) {
        Shoot(*weapon, dir);
    } else {
        Entity* target = nullptr;
        for (auto& entity : Entities) {
            if (entity != entity_ &&
                IsPointInRect(MapPlayerCoord2Global(GetMousePositionMapped()), entity->Get<CollisionCmpt>()->rect)) {
                target = entity;
                break;
            }
        }
        Shoot(*weapon, dir, target);
    }
}
