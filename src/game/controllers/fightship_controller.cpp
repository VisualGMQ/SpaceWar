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

    if (IsLeftPressing()) {
        if (entity_->Has<SpaceshipWeaponCmpt>()) {
            Shoot(*entity_->Use<SpaceshipWeaponCmpt>(),
                  GetMousePosition() - entity_->Get<MoveCmpt>()->position);
        }
    }
}
