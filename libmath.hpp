#pragma once

struct Point {
    float x;
    float y;
};

struct Rect {
    float x;
    float y;
    float w;
    float h;
};

struct Color {
    float r;
    float g;
    float b;
    float a;
};

using Size = Point;
using Rect = Rect;

Point operator+(const Point& p1, const Point& p2);
Point operator-(const Point& p1, const Point& p2);
Point operator*(const Point& p1, const Point& p2);
Point operator/(const Point& p1, const Point& p2);
Point& operator+=(Point& p1, const Point& p2);
Point& operator-=(Point& p1, const Point& p2);
Point& operator*=(Point& p1, const Point& p2);
Point& operator/=(Point& p1, const Point& p2);
