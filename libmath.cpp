#include "libmath.hpp"

Point operator+(const Point& p1, const Point& p2) {
    return Point{p1.x + p2.x, p1.y + p2.y};
}

Point operator-(const Point& p1, const Point& p2) {
    return Point{p1.x - p2.x, p1.y - p2.y};
}

Point operator*(const Point& p1, const Point& p2) {
    return Point{p1.x * p2.x, p1.y * p2.y};
}

Point operator/(const Point& p1, const Point& p2) {
    return Point{p1.x / p2.x, p1.y / p2.y};
}

Point& operator+=(Point& p1, const Point& p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

Point& operator-=(Point& p1, const Point& p2) {
    p1.x -= p2.x;
    p1.y -= p2.y;
    return p1;
}

Point& operator*=(Point& p1, const Point& p2) {
    p1.x *= p2.x;
    p1.y *= p2.y;
    return p1;
}

Point& operator/=(Point& p1, const Point& p2) {
    p1.x /= p2.x;
    p1.y /= p2.y;
    return p1;
}
