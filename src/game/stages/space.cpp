#include "game/stages/space.hpp"

void SpaceScence::OnInit() {
    Renderer::SetClearColor(Color{0, 0, 0, 255});
    LoadResources();

    Entities.Clear();
    Bullets.Clear();

    PlayerSpaceship = CreateFightShip();
    Entities.Add(PlayerSpaceship);
    PlayerSpaceship->Use<MoveCmpt>()->position = Point{400, 400};

    Entity* enemy = CreateFreightShip();
    enemy->Use<MoveCmpt>()->position = Point{100, 100};
    Entities.Add(enemy);

    enemy = CreateFreightShip();
    enemy->Use<MoveCmpt>()->position = Point{200, 100};
    Entities.Add(enemy);

    enemy = CreateFreightShip();
    enemy->Use<MoveCmpt>()->position = Point{100, 200};
    Entities.Add(enemy);

    // freightController_.reset(new FreightShipController(spaceship_));
    fightController_.reset(new FightShipController(PlayerSpaceship));

    gameCamera_.SetAnchor(GameWindowSize / 2);

    SystemMgr.Clear();
    SystemMgr.AddUpdateSystem(new WeaponCooldownSystem);
    SystemMgr.AddUpdateSystem(new MissileUpdateSystem);
    SystemMgr.AddUpdateSystem(new PhysicalSystem);
    SystemMgr.AddUpdateSystem(new ColliRectCorrectSystem);
    SystemMgr.AddUpdateSystem(new CollideSystem);
    SystemMgr.AddUpdateSystem(new CleanupSystem);
    SystemMgr.AddRenderSystem(new RenderEntitySystem);
}

void SpaceScence::OnUpdate(float dt) {
    fightController_->Update(dt);
    SystemMgr.Update(dt);
    gameCamera_.MoveTo(PlayerSpaceship->Get<MoveCmpt>()->position);
}

void SpaceScence::OnRender() {
    Renderer::SetCamera(gameCamera_);
    SystemMgr.Render();

    Renderer::SetCamera(guiCamera_);
    renderGUI();
}

void SpaceScence::renderGUI() {
    Renderer::SetCamera(guiCamera_);

    auto life = PlayerSpaceship->Get<LifeCmpt>()->hp;
    float xOffset = 16 * life;
    for (int i = 0; i < life; i++) {
        Renderer::DrawTile(GameTileSheet->GetTile(1, 1),
                           Point{GameWindowSize.w - xOffset + i * 16, 8});
    }

    renderMiniMap();
    if (PlayerSpaceship->Has<FreightShipCmpt>()) {
        renderWeapons(PlayerSpaceship->Get<FreightShipCmpt>()->weapon, nullptr);
    } else {
        auto fightShip = PlayerSpaceship->Get<FightShipCmpt>();
        renderWeapons(fightShip->weapon1, fightShip->weapon2);
    }
}

void SpaceScence::renderMiniMap() {
    Rect mapRect = {1, 0, 100, 100};
    mapRect.y = GameWindowSize.h - mapRect.h;

    Renderer::SetDrawColor(Color{0, 0, 0, 255});
    Renderer::FillRect(mapRect);
    Renderer::SetDrawColor(Color{255, 255, 255, 255});
    Renderer::DrawRect(mapRect);

    for (auto& entity: Entities) {
        if (entity != PlayerSpaceship) {
            const auto& pos = entity->Get<MoveCmpt>()->position;
            Point entityOnMapPos = (pos - PlayerSpaceship->Get<MoveCmpt>()->position) * Size{mapRect.w, mapRect.h} / GameWindowSize +
                                   Point{mapRect.x, mapRect.y} + Size{mapRect.w, mapRect.h} / 2;
            if (IsPointInRect(entityOnMapPos, mapRect)) {
                if (entity->Has<FreightShipCmpt>()) {
                    Renderer::SetDrawColor(Color{255, 255, 255, 255});
                } else {
                    Renderer::SetDrawColor(Color{0, 0, 255, 255});
                }
                Renderer::FillRect(Rect{entityOnMapPos.x - 1, entityOnMapPos.y - 1, 2, 2});
            }
        }
    }
}

void SpaceScence::renderWeapons(SpaceshipWeaponCmpt* weapon1, SpaceshipWeaponCmpt* weapon2) {
    Rect weaponInfoRect = {0, 0, 300, 100};
    weaponInfoRect.y = GameWindowSize.h - weaponInfoRect.h;
    weaponInfoRect.x = GameWindowSize.w - weaponInfoRect.w - 1;

    Renderer::SetDrawColor(Color{0, 0, 0, 1});
    Renderer::FillRect(weaponInfoRect);
    Renderer::SetDrawColor(Color{1, 1, 1, 1});
    Renderer::DrawRect(weaponInfoRect);

    Point offset = {10, 10};
    auto& font = engine.GetInnerBmpFont();

    if (weapon1) {
        font.Render(weapon1->name,
                    20,
                    Point{weaponInfoRect.x, weaponInfoRect.y} + offset,
                    Color{0, 0.8, 0, 1});
        if (weapon1->bulletAmount != SpaceshipWeaponCmpt::InfBullet) {
            font.Render("[" + std::to_string(weapon1->bulletAmount) + "]",
                        20,
                        Point{weaponInfoRect.x + weaponInfoRect.w - 50, weaponInfoRect.y} + offset,
                        Color{0, 0.8, 0, 1});
        }
        offset.y += 20;
    }
    if (weapon2) {
        font.Render(weapon2->name,
                    20,
                    Point{weaponInfoRect.x, weaponInfoRect.y} + offset,
                    Color{0, 0.8, 0, 1});

        if (weapon2->bulletAmount != SpaceshipWeaponCmpt::InfBullet) {
            font.Render("[" + std::to_string(weapon2->bulletAmount) + "]",
                        20,
                        Point{weaponInfoRect.x + weaponInfoRect.w - 100, weaponInfoRect.y} + offset,
                        Color{0, 0.8, 0, 1});
        }
    }

}

void SpaceScence::OnQuit() {

}
