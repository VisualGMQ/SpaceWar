#pragma once
#include "tinyengine/tinyengine.hpp"

class GameLogoScence final: public Scence {
public:
    void OnInit() override;
    void OnRender() override;

private:
    Camera camera_;
    float initTime_;
    Unique<Sound> sound_;
    bool soundPlayed_;
};


