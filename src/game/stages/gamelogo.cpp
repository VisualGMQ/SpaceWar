#include "game/stages/gamelogo.hpp"

constexpr float TitlePixel = 40.0f;
constexpr float AuthorInfoPixel = 20.0f;
const char* Title = "1M GAMES DEV";
const char* AuthorInfo = "MADE BY VISUALGMQ";

void GameLogoScence::OnInit() {
    Renderer::SetClearColor(Color{0, 0, 0, 255});
    initTime_ = GetTime();
    sound_.reset(new Sound("assets/1mgame_sound.wav"));
    soundPlayed_ = false;
}

void GameLogoScence::OnRender() {
    float duration = GetTime() - initTime_;
    if (duration > 2 && !soundPlayed_) {
        sound_->Play();
        soundPlayed_ = true;
    }
    if (duration < 3) {
        engine.GetInnerBmpFont().Render(Title,
                                        TitlePixel,
                                        Point{0, -25} +
                                        GetCenterAlign(Rect{0, 0,
                                                            engine.GetWindowSize().w,
                                                            engine.GetWindowSize().h},
                                                       Size{TitlePixel * strlen(Title), TitlePixel}),
                                        Color{1, 1, 1, 1});
        engine.GetInnerBmpFont().Render(AuthorInfo,
                                        AuthorInfoPixel,
                                        Point{0, 25} +
                                        GetCenterAlign(Rect{0, 0,
                                                           engine.GetWindowSize().w,
                                                           engine.GetWindowSize().h},
                                                       Size{AuthorInfoPixel * strlen(AuthorInfo), AuthorInfoPixel}),
                                        Color{0.5, 0.5, 0.5, 1});
    }
}
