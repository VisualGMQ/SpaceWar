#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/global.hpp"
#include "game/entity.hpp"
#include "game/system.hpp"
#include "game/controllers/freightship_controller.hpp"
#include "game/controllers/fightship_controller.hpp"
#include "game/ai.hpp"

class SpaceScence: public Scence {
public:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnRender() override;
    void OnQuit() override;

private:
    Unique<FightShipController> fightController_;

    void renderBackground();
    void renderGUI();
    void renderMiniMap();
    void renderWeapons(SpaceshipWeaponCmpt* weapon1, SpaceshipWeaponCmpt* weapon2);

    Camera guiCamera_;
    Camera gameCamera_;

    std::vector<Point> stars_;
};
