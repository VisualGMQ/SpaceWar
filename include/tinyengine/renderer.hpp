#pragma once
#include "pch.hpp"
#include "libmath.hpp"
#include "texture.hpp"
#include "glhelpfunc.hpp"
#include "shader.hpp"
#include "camera.hpp"

class Renderer final {
public:
    static void Init();
    static void Shutdown();
    static void SetClearColor(const Color&);
    static void SetDrawColor(const Color&);
    static void Clear();
    static void DrawLine(const Point& p1, const Point& p2);
    static void DrawRect(const Rect& rect);
    static void FillRect(const Rect& rect);
    static void DrawTexture(const Texture& texture, const Mat44& transform, const Color& color = Color{1, 1, 1, 1});
    static void SetViewport(int x, int y, int w, int h);
    static const Color& GetDrawColor();
    static void SetCamera(Camera& camera);
    static void Update();

private:
    static Color color_;
};
