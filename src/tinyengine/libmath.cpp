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

Point operator*(const Point& p, float value) {
    return Point{p.x * value, p.y * value};
}

Point operator*(float value, const Point& p) {
    return p * value;
}

Point operator/(const Point& p, float value) {
    return Point{p.x / value, p.y / value};
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

Rect RectsIntersect(const Rect& r1, const Rect& r2) {
    float xc1 = std::max(r1.x, r2.x),
          yc1 = std::max(r1.y, r2.y),
          xc2 = std::min(r1.x + r1.w, r2.x + r2.w),
          yc2 = std::min(r1.y + r1.h, r2.y + r2.h);
    return Rect{xc1, yc1, xc2 - xc1, yc2 - yc1};
}

/* Mat44 implementation */
const Mat44 Mat44::Eye = Mat44({1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1});

Mat44::Mat44() {
    Fill(0);
}

Mat44::Mat44(const std::initializer_list<float>& l) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data_[i + j * 4] = *(l.begin() + i * 4 + j);
        }
    }
}

float Mat44::Get(const Point& p) const {
    return data_.at(p.y + p.x * 4);
}

void Mat44::Set(const Point& p, const float& value) {
    data_.at(p.y + p.x * 4) = value;
}

bool Mat44::InMat(const Point& p) const{
    return p.x >= 0 && p.y >= 0 && p.x < 4 && p.y < 4;
}
