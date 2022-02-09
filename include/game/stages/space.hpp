#pragma once

#include "tinyengine/tinyengine.hpp"
#include "game/global.hpp"
#include "game/entity.hpp"
#include "game/system.hpp"
#include "game/controllers/freightship_controller.hpp"
#include "game/controllers/fightship_controller.hpp"

class SpaceScence: public Scence {
public:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnRender() override;
    void OnQuit() override;

private:
    Unique<FreightShipController> freightController_;
    Unique<FightShipController> fightController_;

    void renderGUI();
    void renderMiniMap();
    void renderWeapons(SpaceshipWeaponCmpt* weapon1, SpaceshipWeaponCmpt* weapon2);

    Camera guiCamera_;
    Camera gameCamera_;
};
