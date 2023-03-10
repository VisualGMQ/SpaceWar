#include "game/stages/space.hpp"
#include "game/gui.hpp"
#include "game/stages/select.hpp"

void SpaceScence::OnInit() {
    Renderer::SetClearColor(Color{0, 0, 0, 255});
    Log("Entities size = %ld", Entities.Size());
    Log("Bullets size = %ld", Bullets.Size());
    for (int i = 0; i < 4; i++) {
        Log("Group %d size = %ld", i, Groups[i].Size());
    }

    mode_ = Gaming;

    initEnemies();
    initPlayer();
    calcGroupHps();

    lookAtEntity_ = PlayerSpaceship;
    gameCamera_.SetAnchor(GameWindowSize / 2);

    SystemMgr.Clear();
    SystemMgr.AddUpdateSystem(new AIUpdateSystem);
    SystemMgr.AddUpdateSystem(new WeaponCooldownSystem);
    SystemMgr.AddUpdateSystem(new BulletUpdateSystem);
    SystemMgr.AddUpdateSystem(new PhysicalSystem);
    SystemMgr.AddUpdateSystem(new ColliRectCorrectSystem);
    SystemMgr.AddUpdateSystem(new CollideSystem);
    SystemMgr.AddUpdateSystem(new CleanupSystem);
    SystemMgr.AddRenderSystem(new RenderEntitySystem);

    for (int i = 0; i < 100; i++) {
        Point p{Random<float>(0, GameWindowSize.w),
                Random<float>(0, GameWindowSize.h)};
        stars_.push_back(p);
    }
}

void SpaceScence::calcGroupHps() {
    for (int i = 0; i < InitInfo.groupNum; i++) {
        for (auto& entity : Groups[i]) {
            if (entity->Has<LifeCmpt>()) {
                groupHps[i] += entity->Get<LifeCmpt>()->hp;
            }
        }
    }
}

void SpaceScence::initPlayer() {
    if (PlayerSpaceship && PlayerSpaceship->IsAlive()) {
        ECSContext.DestroyEntity(PlayerSpaceship);
    }
    if (InitInfo.planeType == FightShip) {
        PlayerSpaceship = CreateFightShip(PlayerGroup);
        controller_.reset(new FightShipController(PlayerSpaceship));
    } else if (InitInfo.planeType == FreightShip) {
        PlayerSpaceship = CreateFreightShip(PlayerGroup);
        controller_.reset(new FreightShipController(PlayerSpaceship));
    }
    Entities.Add(PlayerSpaceship);
    Groups[PlayerGroup].Add(PlayerSpaceship);
    PlayerSpaceship->Use<MoveCmpt>()->position = Point{0, 0};
}

void SpaceScence::initEnemies() {
    if (InitInfo.planeType == FightShip) {
        generateEnemiesAt(PlayerGroup, Point{0, 0}, InitInfo.fightShipNum - 1, InitInfo.freightShipNum);
    } else {
        generateEnemiesAt(PlayerGroup, Point{0, 0}, InitInfo.fightShipNum, InitInfo.freightShipNum - 1);
    }
    if (InitInfo.groupNum == 2) {
        generateEnemiesAt(Enemy1Group, Point{0, -720 * 4}, InitInfo.fightShipNum, InitInfo.freightShipNum);
    } else if (InitInfo.groupNum == 3) {
        generateEnemiesAt(Enemy1Group, Point{-720 * 4, -720 * 4}, InitInfo.fightShipNum, InitInfo.freightShipNum);
        generateEnemiesAt(Enemy2Group, Point{720 * 4, -720 * 4}, InitInfo.fightShipNum, InitInfo.freightShipNum);
    } else if (InitInfo.groupNum == 4) {
        generateEnemiesAt(Enemy1Group, Point{0, -720 * 4}, InitInfo.fightShipNum, InitInfo.freightShipNum);
        generateEnemiesAt(Enemy2Group, Point{720 * 4, 0}, InitInfo.fightShipNum, InitInfo.freightShipNum);
        generateEnemiesAt(Enemy3Group, Point{720 * 4, -720 * 4}, InitInfo.fightShipNum, InitInfo.freightShipNum);
    } else {
        Log("group num invalid");
    }
}

void SpaceScence::generateEnemiesAt(int group, const Point& p, int fightShipNum, int freightShipNum) {
    for (int i = 0; i < freightShipNum; i++) {
        Entity* enemy = CreateFreightShip(group);
        enemy->Add<AICmpt>(FreightShipAI);
        enemy->Use<MoveCmpt>()->position += p + Point{Random<float>(-400, 400), Random<float>(-100, 100)};
        Entities.Add(enemy);
        Groups[group].Add(enemy);
    }
    for (int i = 0; i < fightShipNum; i++) {
        Entity* enemy = CreateFightShip(group);
        enemy->Add<AICmpt>(FightShipAI);
        enemy->Use<MoveCmpt>()->position += p + Point{Random<float>(-400, 400), Random<float>(-100, 100)};
        Entities.Add(enemy);
        Groups[group].Add(enemy);
    }
}

void SpaceScence::OnUpdate(float dt) {
    if (PlayerSpaceship && PlayerSpaceship->IsAlive()) {
        controller_->Update(dt);
    }
    SystemMgr.Update(dt);
    
    if (PlayerSpaceship && !PlayerSpaceship->IsAlive()) {
        PlayerSpaceship = nullptr;
    }

    if (lookAtEntity_ && lookAtEntity_->IsAlive()) {
        gameCamera_.MoveTo(lookAtEntity_->Get<MoveCmpt>()->position);
    } else {
        if (!Groups[PlayerGroup].Empty()) {
            lookAtEntity_ = *Groups[PlayerGroup].begin();
        }
    }

    if (!PlayerSpaceship || !PlayerSpaceship->IsAlive()) {
        if (IsKeyPressing(GLFW_KEY_SPACE)) {
            PlayerSpaceship = lookAtEntity_;
            if (PlayerSpaceship->Has<AICmpt>()) {
                PlayerSpaceship->Remove<AICmpt>();
            }
            attachController();
        }
    }

    if (Groups[PlayerGroup].Empty()) {
        mode_ = Lost;
    }
    bool win = true;
    for (int i = 1; i < 4; i++) {
        win = win && Groups[i].Empty();
    }
    if (win) {
        mode_ = Win;
    }
}

void SpaceScence::attachController() {
    if (PlayerSpaceship->Has<FreightShipCmpt>()) {
        controller_.reset(new FreightShipController(PlayerSpaceship));
    } else {
        controller_.reset(new FightShipController(PlayerSpaceship));
    }
}

void SpaceScence::OnRender() {
    Renderer::SetCamera(gameCamera_);
    renderBackground();
    SystemMgr.Render();

    Renderer::SetCamera(guiCamera_);
    renderGUI();

    auto& font = engine.GetInnerBmpFont();
    if (mode_ == Win) {
        font.Render("WIN", 40, GameWindowSize / 2 - Point{60, 60}, Color{0, 1, 0, 1});
    } else if (mode_ == Lost) {
        font.Render("LOST", 40, GameWindowSize / 2 - Point{80, 60}, Color{1, 0, 0, 1});
    }
    if (mode_ != Gaming) {
        std::string msg = "PRESS SPACE TO RESTART";
        font.Render(msg, 20, GameWindowSize / 2 - Point{msg.length() * 20 / 2.0f, 0}, Color{1, 1, 1, 1});
        if (IsKeyPressing(GLFW_KEY_SPACE)) {
            engine.ChangeScence(new SelectScence);
        }
    }
}

void SpaceScence::renderBackground() {
    Renderer::SetDrawColor(Color{1, 1, 1, 1});

    Point p;
    p.x = std::floor(gameCamera_.GetPosition().x / GameWindowSize.w) * GameWindowSize.w;
    p.y = std::floor(gameCamera_.GetPosition().y / GameWindowSize.h) * GameWindowSize.h;

    for (auto& star : stars_) {
        Point pos{p.x + star.x, p.y + star.y};
        if (pos.x < gameCamera_.GetPosition().x) {
            pos.x += GameWindowSize.w;
        }
        if (pos.y < gameCamera_.GetPosition().y) {
            pos.y += GameWindowSize.h;
        }
        Rect drawrect = {pos.x - GameWindowSize.w / 2, pos.y - GameWindowSize.h / 2, 2, 2};
        Renderer::FillRect(drawrect);
    }
}

void SpaceScence::renderGUI() {
    Renderer::SetCamera(guiCamera_);

    int life = 0;
    if (PlayerSpaceship && PlayerSpaceship->IsAlive() && PlayerSpaceship->Has<LifeCmpt>()) {
        life = PlayerSpaceship->Get<LifeCmpt>()->hp;
    }
    float xOffset = 16 * life;
    for (int i = 0; i < life; i++) {
        Renderer::DrawTile(GameTileSheet->GetTile(5, 0),
                           Point{GameWindowSize.w - xOffset + i * 16, 8});
    }

    renderMiniMap();
    if (PlayerSpaceship && PlayerSpaceship->IsAlive()) {
        if (PlayerSpaceship->Has<FreightShipCmpt>()) {
            renderWeapons(PlayerSpaceship->Get<FreightShipCmpt>()->weapon, nullptr);
        } else {
            if (PlayerSpaceship->Has<FightShipCmpt>()) {
                auto fightShip = PlayerSpaceship->Get<FightShipCmpt>();
                renderWeapons(fightShip->weapon1, fightShip->weapon2);
            }
        }
    }

    drawGroupHp();
}

void SpaceScence::drawGroupHp() {
    static Color colors[4] = {Color{1, 0, 0, 1},
                              Color{0, 1, 0, 1},
                              Color{0, 0, 1, 1},
                              Color{1, 1, 0, 1}};

    for (int i = 0; i < InitInfo.groupNum; i++) {
        int hp = 0;
        for (auto& entity : Groups[i]) {
            if (entity->Has<LifeCmpt>()) {
                hp += entity->Get<LifeCmpt>()->hp;
            }
        }
        Renderer::SetDrawColor(colors[i]);
        Renderer::FillRect(Rect{150, GameWindowSize.h - 20 * (i + 1), hp / float(groupHps[i]) * 500, 20});
        Renderer::SetDrawColor(Color{1, 1, 1, 1});
        Renderer::DrawRect(Rect{150, GameWindowSize.h - 20 * (i + 1), 500, 20});
    }
}

void SpaceScence::renderMiniMap() {
    Rect mapRect = {1, 0, 100, 100};
    mapRect.y = GameWindowSize.h - mapRect.h;

    Renderer::SetDrawColor(Color{0, 0, 0, 255});
    Renderer::FillRect(mapRect);
    Renderer::SetDrawColor(Color{255, 255, 255, 255});
    Renderer::DrawRect(mapRect);

    if (!PlayerSpaceship || !PlayerSpaceship->IsAlive()) {
        return;
    }

    for (auto& entity: Entities) {
        if (entity != PlayerSpaceship) {
            if (!entity->Has<MoveCmpt>()) continue;
            const auto& pos = entity->Get<MoveCmpt>()->position;
            Point entityOnMapPos = (pos - PlayerSpaceship->Get<MoveCmpt>()->position) * Size{mapRect.w, mapRect.h} / (GameWindowSize * 8) +
                                   Point{mapRect.x, mapRect.y} + Size{mapRect.w, mapRect.h} / 2;
            if (IsPointInRect(entityOnMapPos, mapRect)) {
                if (entity->Has<GroupCmpt>()) {
                    Renderer::SetDrawColor(GroupSpecColor[entity->Get<GroupCmpt>()->groupIdx]);
                }
                Renderer::FillRect(Rect{entityOnMapPos.x - 1, entityOnMapPos.y - 1, 2, 2});
            }
        }
    }
    Renderer::SetDrawColor(Color{1, 1, 1, 1});
    Renderer::FillRect(Rect{mapRect.x + mapRect.w / 2, mapRect.y + mapRect.h / 2,
                            2, 2});
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
        offset.y += 20;
    }
}

void SpaceScence::OnQuit() {
    auto destroyFunc = [&](const EntityPtr& entity){
        ECSContext.DestroyEntity(entity);
    };

    for (int i = 0; i < 4; i++) {
        Groups[i].Clear();
    }
    Entities.Clear(nullptr, destroyFunc);
    Bullets.Clear(nullptr, destroyFunc);
}
