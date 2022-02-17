#include "game/stages/welcome.hpp"
#include "game/gui.hpp"
#include "game/constants.hpp"
#include "game/stages/select.hpp"
#include "game/global.hpp"

void WelcomeScence::OnInit() {
    Renderer::SetClearColor(Color{0.1, 0.1, 0.1, 1});

    startImage_.reset(new Texture("assets/start_btn.png"));
    exitImage_.reset(new Texture("assets/exit_btn.png"));

    GLFWimage image;
    image.pixels = stbi_load("assets/cursor.png", &image.width, &image.height, nullptr, 0);
    auto cursor = glfwCreateCursor(&image, image.width / 2, image.height / 2);
    glfwSetCursor(engine.GetWindow(), cursor);
    stbi_image_free(image.pixels);

    LoadResources();
}

void WelcomeScence::OnRender() {
    Renderer::SetCamera(camera_);
    auto& font = engine.GetInnerBmpFont();
    std::string title = "SPACE WAR";
    int pt = 70;
    font.Render(title, pt,
                Point{(GameWindowSize.w - title.size() * pt) / 2, 100},
                Color{0.39, 0.6, 1, 1});

    title = "-------MADE FOR 1M GAMES-------";
    pt = 20;
    font.Render(title, pt,
                Point{(GameWindowSize.w - title.size() * pt) / 2, 200},
                Color{0.8, 0.8, 1, 1});

    title = "HTTPS://GITEE.COM/VISUALGMQ/SPACE-WAR.GIT";
    pt = 10;
    font.Render(title, pt,
                Point{(GameWindowSize.w - title.size() * pt) / 2, 710},
                Color{0.8, 0.8, 1, 1});

    if (Button(exitImage_.get(), Point{(GameWindowSize.w) / 2, 550}, Size{100, 100})) {
        engine.Exit();
    }

    if (Button(startImage_.get(), Point{(GameWindowSize.w) / 2, 400}, Size{100, 100})) {
        engine.ChangeScence(new SelectScence);
    }
}
