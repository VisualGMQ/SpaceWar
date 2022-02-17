#include "game/controllers/freightship_controller.hpp"
#include "tinyengine/event.hpp"

FreightShipController::FreightShipController(Entity* entity)
    : entity_(entity) {}

void FreightShipController::Update(float dt) {
    if (!entity_ || !entity_->IsAlive()) {
        return;
    }

    const float spd = 100;
    auto motionCmpt = entity_->Use<MotionCmpt>();
    if (IsKeyPressing(GLFW_KEY_A)) {
        MoveLeft(*motionCmpt);
    }
    if (IsKeyPressing(GLFW_KEY_D)) {
        MoveRight(*motionCmpt);
    }
    if (IsKeyPressing(GLFW_KEY_S)) {
        MoveDown(*motionCmpt);
    }
    if (IsKeyPressing(GLFW_KEY_W)) {
        MoveUp(*motionCmpt);
    }

    if (IsLeftPressing()) {
        auto weapon = entity_->Use<FreightShipCmpt>()->weapon;
        if (weapon) {
            if (weapon->type == SpaceshipWeaponCmpt::Orientation) {
                Shoot(*weapon,
                      Rotate(Point{0, -1}, entity_->Get<FightShipCmpt>()->degree));
            } else {
                Shoot(*weapon,
                      GetMousePositionMapped() - GameWindowSize / 2);
            }
        }
    }
}
