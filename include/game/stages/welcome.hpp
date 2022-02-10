#pragma once

#include "tinyengine/tinyengine.hpp"

class WelcomeScence: public Scence {
public:
    void OnInit() override;
    void OnRender() override;

private:
    Unique<Texture> startImage_;
    Unique<Texture> exitImage_;
    Camera camera_;
};
