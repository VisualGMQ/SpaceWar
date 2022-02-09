#include "game/controllers/freightship_controller.hpp"
#include "tinyengine/event.hpp"

FreightShipController::FreightShipController(Entity* entity)
    : entity_(entity) {}

void FreightShipController::Update(float dt) {
    const float spd = 100;
    auto motionCmpt = entity_->Use<MotionCmpt>();
    if (IsKeyPressing(GLFW_KEY_A)) {
        motionCmpt->acceleration += Point{-spd, 0};
    }
    if (IsKeyPressing(GLFW_KEY_D)) {
        motionCmpt->acceleration += Point{spd, 0};
    }
    if (IsKeyPressing(GLFW_KEY_S)) {
        motionCmpt->acceleration += Point{0, spd};
    }
    if (IsKeyPressing(GLFW_KEY_W)) {
        motionCmpt->acceleration += Point{0, -spd};
    }

    if (IsLeftPressing()) {
        auto weapon = entity_->Use<FreightShipCmpt>()->weapon;
        if (weapon) {
            // FIXME duplicated codes in here and fightship_controller.cpp
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
