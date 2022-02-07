#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/global.hpp"
#include "game/entity.hpp"
#include "game/system.hpp"
#include "game/controllers/spaceship_controller.hpp"

class SpaceScence: public Scence {
public:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnRender() override;
    void OnQuit() override;

private:
    Entity* spaceship_;
    Unique<FreeRotationController> controller_;
};
