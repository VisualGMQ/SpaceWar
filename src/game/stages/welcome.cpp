#include "game/stages/welcome.hpp"
#include "game/gui.hpp"
#include "game/stages/space.hpp"

void WelcomeScence::OnInit() {
    startImage_.reset(new Texture("assets/start_btn.png"));
    exitImage_.reset(new Texture("assets/exit_btn.png"));
}

void WelcomeScence::OnRender() {
    Renderer::SetCamera(camera_);
    auto& font = engine.GetInnerBmpFont();
    std::string title = "SPACE SECTOR";
    int pt = 70;
    font.Render(title, pt,
                Point{(GameWindowSize.w - title.size() * pt) / 2, 100},
                Color{0.39, 0.6, 1, 1});

    title = "-------MADE FOR 1M GAMES-------";
    pt = 20;
    font.Render(title, pt,
                Point{(GameWindowSize.w - title.size() * pt) / 2, 200},
                Color{0.8, 0.8, 1, 1});

    if (Button(exitImage_.get(), Point{(GameWindowSize.w) / 2, 550}, Size{100, 100})) {
        engine.Exit();
    }

    if (Button(startImage_.get(), Point{(GameWindowSize.w) / 2, 400}, Size{100, 100})) {
        engine.ChangeScence(new SpaceScence);
    }
}
