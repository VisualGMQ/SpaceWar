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
    enum GameMode {
        Gaming = 1,
        Lost = 2,
        Win = 3,
    };

    Unique<Controller> controller_;

    Camera guiCamera_;
    Camera gameCamera_;
    Entity* lookAtEntity_;
    GameMode mode_;

    std::vector<Point> stars_;
    int groupHps[4] = {0};

    void renderBackground();
    void renderGUI();
    void renderMiniMap();
    void renderWeapons(SpaceshipWeaponCmpt* weapon1, SpaceshipWeaponCmpt* weapon2);
    void initEnemies();
    void attachController();
    void generateEnemiesAt(int group, const Point& p, int fightShipNum, int freightShipNum);
    void initPlayer();
    void calcGroupHps();
    void drawGroupHp();
};
