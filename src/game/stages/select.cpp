#include "game/stages/select.hpp"
#include "game/constants.hpp"
#include "game/gui.hpp"
#include "game/global.hpp"
#include "game/stages/space.hpp"

void SelectScence::OnInit() {
    Renderer::SetClearColor(Color{0.1, 0.1, 0.1, 1});

    switchBtn_.reset(new Texture("assets/switch_btn.png"));
    goBtn_.reset(new Texture("assets/go_btn.png"));

    Renderer::SetCamera(camera_);
    InitInfo.planeType = 1;
    InitInfo.fightShipNum = 3;
    InitInfo.freightShipNum = 2;
    InitInfo.groupNum = 2;
}

void SelectScence::OnRender() {
    renderTitle();
    renderSelectTitle();
    renderSelectShip();
    renderProperties();

    renderConfigTitle();
    renderGroupNumPanel();
    renderPlaneNumPanel();

    renderGoBtn();
}

void SelectScence::renderTitle() {
    std::string title = "PREPARATION ROOM";
    engine.GetInnerBmpFont().Render(title,
                                    40,
                                    Point{(GameWindowSize.w - title.length() * 40) / 2, 50},
                                    Color{0.5, 0.5, 0, 1});
}

void SelectScence::renderSelectTitle() {
    engine.GetInnerBmpFont().Render("SELECT PLANE",
                                    30,
                                    Point{80, 150},
                                    Color{0.2, 0.2, 0.8, 1});
}

void SelectScence::renderConfigTitle() {
    engine.GetInnerBmpFont().Render("CONFIG WAR",
                                    30,
                                    Point{600, 150},
                                    Color{0.2, 0.2, 0.8, 1});
}

void SelectScence::renderSelectShip() {
    if (Button(switchBtn_.get(), Point{100, 300}, switchBtn_->GetSize() * 2)) {
        InitInfo.planeType ++;
        if (InitInfo.planeType > 2) {
            InitInfo.planeType = 1;
        }
    }
    if (Button(switchBtn_.get(), Point{400, 300}, switchBtn_->GetSize() * 2, true)) {
        InitInfo.planeType --;
        if (InitInfo.planeType < 1) {
            InitInfo.planeType = 2;
        }
    }

    static float rotation = 0;
    if (InitInfo.planeType == FreightShip) {
        Renderer::DrawTile(GameTileSheet->GetTile(0, 0),
                           Point{250, 300},
                           Size{64, 64},
                           rotation);
    } else if (InitInfo.planeType == FightShip) {
        Renderer::DrawTile(GameTileSheet->GetTile(1, 0),
                           Point{250, 300},
                           Size{64, 64},
                           rotation);
    }
    rotation += 2;
}

void SelectScence::renderProperties() {
    auto& font = engine.GetInnerBmpFont();
    if (InitInfo.planeType == FreightShip) {
        font.Render("FREIGHT SHIP",
                    20,
                    Point{80, 380},
                    Color{0.8, 0.1, 0.8, 1});
        font.Render("HP: " + std::to_string(FreightShipLife),
                    20,
                    Point{80, 400},
                    Color{1, 0.1, 0.1, 1});
        font.Render("MAX SPEED: " + std::to_string(int(FreightShipMaxSpeed)),
                    20,
                    Point{80, 420},
                    Color{1, 1, 0, 1});
        font.Render("MAX ACCELERATION: " + std::to_string(int(FreightShipAccelerate)),
                    20,
                    Point{80, 440},
                    Color{0.7, 0.7, 0, 1});
        font.Render("FREE SLOW SHOOT",
                    20,
                    Point{80, 460},
                    Color{0, 0.7, 0.7, 1});
        font.Render("FREE MOVE",
                    20,
                    Point{80, 480},
                    Color{0, 0.7, 0.7, 1});
        font.Render("ONE WEAPON",
                    20,
                    Point{80, 500},
                    Color{0, 0.7, 0.7, 1});
    } else if (InitInfo.planeType == FightShip) {
        font.Render("FIGHT SHIP",
                    20,
                    Point{80, 380},
                    Color{0.8, 0.1, 0.8, 1});
        font.Render("HP: " + std::to_string(FightShipLife),
                    20,
                    Point{80, 400},
                    Color{1, 0.1, 0.1, 1});
        font.Render("MAX SPEED: " + std::to_string(int(FightShipMaxSpeed)),
                    20,
                    Point{80, 420},
                    Color{1, 1, 0, 1});
        font.Render("MAX ACCELERATION: " + std::to_string(int(FightShipAccelration)),
                    20,
                    Point{80, 440},
                    Color{0.7, 0.7, 0, 1});
        font.Render("DIRECT FAST SHOOT",
                    20,
                    Point{80, 460},
                    Color{0, 0.7, 0.7, 1});
        font.Render("DIRECT MOVE",
                    20,
                    Point{80, 480},
                    Color{0, 0.7, 0.7, 1});
        font.Render("TWO WEAPON",
                    20,
                    Point{80, 500},
                    Color{0, 0.7, 0.7, 1});
    }
}

void SelectScence::renderGroupNumPanel() {
    auto& font = engine.GetInnerBmpFont();
    font.Render("GROUP NUMBER:",
                 20,
                 Point{600, 300},
                 Color{0.6, 0.3, 0.8, 1});

    if (Button(switchBtn_.get(), Point{870, 310}, Size{switchBtn_->GetSize().w, 20})) {
        InitInfo.groupNum --;
        if (InitInfo.groupNum <= 1)
            InitInfo.groupNum = 4;
    }
    font.Render(std::to_string(InitInfo.groupNum), 20, Point{890, 300}, Color{0.6, 0.3, 0.8, 1});
    if (Button(switchBtn_.get(), Point{920, 310}, Size{switchBtn_->GetSize().w, 20}, true)) {
        InitInfo.groupNum ++;
        if (InitInfo.groupNum > 4)
            InitInfo.groupNum = 2;
    }
}

void SelectScence::renderPlaneNumPanel() {
    auto& font = engine.GetInnerBmpFont();

    font.Render("FIGHTSHIPS:",
                 20,
                 Point{600, 400},
                 Color{0.3, 0.6, 0.8, 1});

    if (Button(switchBtn_.get(), Point{870, 410}, Size{switchBtn_->GetSize().w, 20})) {
        InitInfo.fightShipNum --;
        if (InitInfo.fightShipNum <= 0)
            InitInfo.fightShipNum = 100;
    }
    font.Render(std::to_string(InitInfo.fightShipNum), 20, Point{890, 400}, Color{0.6, 0.3, 0.8, 1});
    if (Button(switchBtn_.get(), Point{960, 410}, Size{switchBtn_->GetSize().w, 20}, true)) {
        InitInfo.fightShipNum ++;
        if (InitInfo.fightShipNum> 100)
            InitInfo.fightShipNum = 1;
    }

    font.Render("FREIGHTSHIPS:",
                 20,
                 Point{600, 420},
                 Color{0.3, 0.6, 0.8, 1});

    if (Button(switchBtn_.get(), Point{870, 430}, Size{switchBtn_->GetSize().w, 20})) {
        InitInfo.freightShipNum --;
        if (InitInfo.freightShipNum <= 0)
            InitInfo.freightShipNum = 100;
    }
    font.Render(std::to_string(InitInfo.freightShipNum), 20, Point{890, 420}, Color{0.6, 0.3, 0.8, 1});
    if (Button(switchBtn_.get(), Point{960, 430}, Size{switchBtn_->GetSize().w, 20}, true)) {
        InitInfo.freightShipNum ++;
        if (InitInfo.freightShipNum> 100)
            InitInfo.freightShipNum = 1;
    }

}

void SelectScence::renderGoBtn() {
    if (Button(goBtn_.get(),
               Point{800, 600},
               goBtn_->GetSize() * 4)) {
        engine.ChangeScence(new SpaceScence);
    } else {
        engine.GetInnerBmpFont().Render("GO", 40, Point{760, 570}, Color{1, 0, 1, 1});
    }
}
