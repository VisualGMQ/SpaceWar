#include "game/controllers/freightship_controller.hpp"
#include "tinyengine/event.hpp"

FreightShipController::FreightShipController(Entity* entity)
    : entity_(entity) {}

void FreightShipController::Update(float dt) {
    const float spd = 100;
    auto motionCmpt = entity_->Use<MotionCmpt>();
    if (IsKeyPressing(GLFW_KEY_A)) {
        // motionCmpt->speed += Point{-spd, 0};
        motionCmpt->acceleration += Point{-spd, 0};
        // motionCmpt->speed.x = -spd;
    }
    if (IsKeyPressing(GLFW_KEY_D)) {
        // motionCmpt->speed += Point{spd, 0};
        motionCmpt->acceleration += Point{spd, 0};
        // motionCmpt->speed.x = spd;
    }
    if (IsKeyPressing(GLFW_KEY_S)) {
        // motionCmpt->speed += Point{0, spd};
        motionCmpt->acceleration += Point{0, spd};
        // motionCmpt->speed.y = spd;
    }
    if (IsKeyPressing(GLFW_KEY_W)) {
        // motionCmpt->speed += Point{0, -spd};
        motionCmpt->acceleration += Point{0, -spd};
        // motionCmpt->speed.y = -spd;
    }

    if (IsLeftPressing()) {
        if (entity_->Has<SpaceshipWeaponCmpt>()) {
            // FIXME duplicated codes in here and fightship_controller.cpp
            auto weapon = entity_->Use<SpaceshipWeaponCmpt>();
            if (weapon->type == SpaceshipWeaponCmpt::Orientation) {
                Shoot(*weapon,
                      Rotate(Point{0, -1}, entity_->Get<FightShipCmpt>()->degree));
            } else {
                Shoot(*weapon,
                      GetMousePosition() - entity_->Get<MoveCmpt>()->position);
            }
        }
    }
}
