#pragma once

#include "game/controller.hpp"
#include "tinyengine/tinyengine.hpp"
#include "game/entity.hpp"
#include "game/component.hpp"
#include "game/action.hpp"

class FreeRotationController: public Controller {
public:
    FreeRotationController(Entity* entity);
    void Update(float dt) override;

private:
    Entity* entity_;
};
