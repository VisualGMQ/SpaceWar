#include "game/stages/space.hpp"

void SpaceScence::OnInit() {
    Renderer::SetClearColor(Color{0, 0, 0, 255});
    LoadResources();

    spaceship_ = CreateFightShip();
    Entities.Add(spaceship_);
    spaceship_->Use<MoveCmpt>()->position = Point{400, 400};

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
    fightController_.reset(new FightShipController(spaceship_));

    SystemMgr.Clear();
    SystemMgr.AddUpdateSystem(new BulletCooldownSystem);
    SystemMgr.AddUpdateSystem(new PhysicalSystem);
    SystemMgr.AddUpdateSystem(new ColliRectCorrectSystem);
    SystemMgr.AddUpdateSystem(new CollideSystem);
    SystemMgr.AddUpdateSystem(new CleanupSystem);
    SystemMgr.AddRenderSystem(new RenderEntitySystem);
}

void SpaceScence::OnUpdate(float dt) {
    fightController_->Update(dt);
    SystemMgr.Update(dt);
}

void SpaceScence::OnRender() {
    Renderer::SetCamera(gameCamera_);
    SystemMgr.Render();
    renderGUI();
}

void SpaceScence::renderGUI() {
    Renderer::SetCamera(guiCamera_);

    auto life = spaceship_->Get<LifeCmpt>()->hp;
    float xOffset = 16 * life;
    for (int i = 0; i < life; i++) {
        Renderer::DrawTile(GameTileSheet->GetTile(1, 1),
                           Point{GameWindowWidth - xOffset + i * 16, 8});
    }
}

void SpaceScence::OnQuit() {

}
