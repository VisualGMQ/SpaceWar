#pragma once
#include "libmath.hpp"
#include "texture.hpp"
#include "pch.hpp"
#include "glhelpfunc.hpp"

class Renderer final {
public:
    static void Init();
    static void Shutdown();
    static void SetClearColor(const Color& color);
    static void SetDrawColor(const Color& color);
    static void Clear();
    static void DrawLine(const Point& p1, const Point& p2);
    static void DrawRect(const Rect& rect);
    static void FillRect(const Rect& rect);
    static void SetViewport(int x, int y, int w, int h);
};
