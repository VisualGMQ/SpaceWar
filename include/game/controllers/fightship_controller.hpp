#pragma once

#include "game/controller.hpp"
#include "tinyengine/tinyengine.hpp"
#include "game/entity.hpp"
#include "game/component.hpp"
#include "game/action.hpp"

class FightShipController: public Controller {
public:
    FightShipController(Entity* entity);
    void Update(float dt) override;

private:
    Entity* entity_;

    void weaponShoot(SpaceshipWeaponCmpt* weapon, const MoveCmpt& move);
};
