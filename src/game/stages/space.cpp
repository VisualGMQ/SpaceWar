#include "game/stages/space.hpp"

void SpaceScence::OnInit() {
    Renderer::SetClearColor(Color{0, 0, 0, 255});
    LoadResources();

    spaceship_ = CreateFreightShip();
    Entities.push_back(spaceship_);
    spaceship_->Use<MoveCmpt>()->position = Point{400, 400};

    controller_.reset(new FreeRotationController(spaceship_));

    SystemMgr.Clear();
    SystemMgr.AddRenderSystem(new RenderEntitySystem);
    SystemMgr.AddUpdateSystem(new BulletCooldownSystem);
    SystemMgr.AddUpdateSystem(new PhysicalSystem);
    SystemMgr.AddUpdateSystem(new ColliRectCorrectSystem);
    SystemMgr.AddUpdateSystem(new CleanupSystem);
}

void SpaceScence::OnUpdate(float dt) {
    controller_->Update(dt);
    SystemMgr.Update(dt);
}

void SpaceScence::OnRender() {
    SystemMgr.Render();
}

void SpaceScence::OnQuit() {

}
