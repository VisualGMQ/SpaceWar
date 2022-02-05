#pragma once
#include "pch.hpp"
#include "libmath.hpp"
#include "texture.hpp"
#include "glhelpfunc.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "tilesheet.hpp"

struct Vertex {
    Point pos;
    Point texcoord;
};

class Renderer final {
public:
    enum FlipFlag {
        NoFlip = 0,
        Vertical = 0x01,
        Horizontal = 0x02,
        Both = 0x03,
    };

    static void Init();
    static void Shutdown();
    static void SetClearColor(const Color&);
    static void SetDrawColor(const Color&);
    static void Clear();
    static void DrawLine(const Point& p1, const Point& p2);
    static void DrawRect(const Rect& rect);
    static void FillRect(const Rect& rect);
    static void DrawTile(const Tile& tile,
                         const Point& pos,
                         const Size& size = {0, 0},
                         float degree = 0,
                         FlipFlag flip = NoFlip);
    static void DrawTexture(const Texture* texture,
                            const Rect* srcrect,
                            const Point& pos,
                            const Size& size = Size{0, 0},
                            float degree = 0,
                            FlipFlag flip = NoFlip);
    static void DrawTexture(const Texture* texture,
                            const Rect* rect,
                            const Mat44& transform,
                            const Color& color = Color{1, 1, 1, 1});
    static void SetViewport(int x, int y, int w, int h);
    static const Color& GetDrawColor();
    static void SetCamera(Camera& camera);
    static void Update();

private:
    static Color color_;

    static void drawRectFrag(const Texture* texture,
                             const std::array<Vertex, 6>& vertices,
                             const Mat44& transform,
                             const Color& color);
};
