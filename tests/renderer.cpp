#include "tinyengine/tinyengine.hpp"
#include "unittest.hpp"

class TestRenderer: public Scence {
public:
    void OnInit() override {
        dirt_.reset(new Texture("assets/test/dirt.png"));
        start_.reset(new Texture("assets/test/start.bmp"));
    }

    void OnRender() override {
        Renderer::SetDrawColor(Color{1, 0, 0});
        Renderer::DrawLine(Point{0, 0}, Point{1024, 720});
        Renderer::DrawRect(Rect{100, 100, 50, 75});

        Renderer::SetDrawColor(Color{0, 1, 0});
        Renderer::FillRect(Rect{100, 100, 50, 75});
        
        Renderer::DrawTexture(*dirt_, CreateTextureTransform(dirt_->GetSize(), Point{50, 50}));
        Renderer::DrawTexture(*start_, CreateTextureTransform(dirt_->GetSize(), Point{100, 50}));
    }

private:
    Unique<Texture> dirt_;
    Unique<Texture> start_;
};

RUN_WINDOW("test renderer", 1024, 720, TestRenderer)
