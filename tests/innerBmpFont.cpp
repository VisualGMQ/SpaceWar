#include "tinyengine/tinyengine.hpp"

class TestInnerBmpFont: public Scence {
    void OnInit() override {
        Renderer::SetClearColor(Color{1, 1, 1, 1});
    }

    void OnRender() override {
        auto& font = engine.GetInnerBmpFont();
        for (char c = '0'; c <= '9'; c++) {
            font.RenderChar(c, 8, Point{8.0f * (c - '0'), 0.0f}, Color{0, 0, 0, 1});
        }
        for (char c = '0'; c <= '9'; c++) {
            font.RenderChar(c, 16, Point{16.0f * (c - '0'), 16.0f}, Color{0, 1, 1, 1});
        }

        font.Render("THIS IS INNER FONT", 10, Point{0, 64}, Color{0, 0, 0});
    }
};

RUN_WINDOW("test inner bitmap font", 1024, 720, TestInnerBmpFont)
