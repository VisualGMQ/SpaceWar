#include "tinyengine/tinyengine.hpp"
#include "unittest.hpp"

class TestRenderer: public Scence {
public:
    void OnInit() override {
        dirt_.reset(new Texture("assets/test/dirt.png"));
        start_.reset(new Texture("assets/test/start.png"));
        tilesheet_.reset(new TileSheet("assets/test/tilesheet.png", 8, 1));
        degree_ = 0;
    }

    void OnUpdate(float second) override {
        if (degree_ > 360) {
            degree_ -= 360;
        }
        degree_ += 40 * second;
    }

    void OnRender() override {
        Renderer::SetDrawColor(Color{1, 0, 0});
        Renderer::DrawLine(Point{0, 0}, Point{1024, 720});
        Renderer::DrawRect(Rect{100, 100, 50, 75});

        Renderer::SetDrawColor(Color{0, 1, 0});
        Renderer::FillRect(Rect{100, 100, 50, 75});

        Renderer::DrawTexture(dirt_.get(), nullptr, CreateSRT(Point{50, 50}, dirt_->GetSize(), 0));
        Renderer::DrawTexture(start_.get(), nullptr, Point{100, 50}, Size{0, 0}, degree_);

        Renderer::DrawTexture(tilesheet_->GetTexture(), nullptr, Point{100, 100});
        Renderer::DrawTexture(tilesheet_->GetTexture(), nullptr, Point{100, 116}, Size{0, 0}, 0, Renderer::Horizontal);
        Renderer::DrawTexture(tilesheet_->GetTexture(), nullptr, Point{100, 132}, Size{0, 0}, 0, Renderer::Vertical);
        Renderer::DrawTexture(tilesheet_->GetTexture(), nullptr, Point{100, 148}, Size{0, 0}, 0, Renderer::Both);
        Size tileSize = {16, 16};
        for (int i = 0; i < 8; i++) {
            Rect rect{i * 16.0f, 0, 16, 16};
            Renderer::DrawTile(tilesheet_->GetTile(i, 0), Point{50 + 16.0f * i, 200}, Size{0, 0}, degree_);
        }
    }

private:
    Unique<Texture> dirt_;
    Unique<Texture> start_;
    Unique<TileSheet> tilesheet_;
    float degree_;
};

RUN_WINDOW("test renderer", 1024, 720, TestRenderer)
