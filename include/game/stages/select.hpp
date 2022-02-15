#pragma once

#include "tinyengine/tinyengine.hpp"

class SelectScence: public Scence {
public:
    void OnInit() override;
    void OnRender() override;

private:
    Unique<Texture> switchBtn_;
    Unique<Texture> goBtn_;
    Camera camera_;

    void renderTitle();
    void renderSelectTitle();
    void renderConfigTitle();
    void renderSelectShip();
    void renderProperties();
    void renderGoBtn();
    void renderGroupNumPanel();
    void renderPlaneNumPanel();
};
