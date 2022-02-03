#pragma once

#include "pch.hpp"

inline constexpr bool feq(float v1, float v2) {
    return std::abs(v1 - v2) < std::numeric_limits<float>::epsilon();
}

struct Point {
    union {
        float x;
        float w;
    };
    union {
        float y;
        float h;
    };
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
Point operator*(const Point& p, float value);
Point operator*(float value, const Point& p);
Point operator/(const Point& p, float value);
Point& operator+=(Point& p1, const Point& p2);
Point& operator-=(Point& p1, const Point& p2);
Point& operator*=(Point& p1, const Point& p2);
Point& operator/=(Point& p1, const Point& p2);

inline float Len2(const Point& p) {
    return p.x * p.x + p.y * p.y;
}

inline float Len(const Point& p) {
    return std::sqrt(Len2(p));
}

inline Point Normalize(const Point& p) {
    return p / Len(p);
}

template <typename T>
T Random(const T& low, const T& high) {
    static_assert(std::is_floating_point<T>::value || std::is_integral<T>::value);

    std::random_device device;
    if (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dist(low, high);
        return dist(device);
    } else {
        std::uniform_int_distribution<T> dist(low, high);
        return dist(device);
    }
}

inline char Sign(float value) {
    if (value > 0)
        return 1;
    else if (value < 0)
        return -1;
    else
        return 0;
}

inline float Clamp(float min, float max, float value) {
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

inline bool IsRectsIntersect(const Rect& r1, const Rect& r2) {
    return !(r1.x > r2.x + r2.w ||
             r1.x + r1.w < r2.x ||
             r1.y > r2.x + r2.h ||
             r1.y + r1.h < r2.y);
}

Rect RectsIntersect(const Rect& r1, const Rect& r2);

inline bool IsPointInRect(const Point& p, const Rect& r) {
    return r.x <= p.x && r.y <= p.y && r.x + r.w >= p.x && r.y + r.h >= p.y;
}

/* a matrix stored in row major*/
class Mat44{
public:
    static const Mat44 Eye;

    Mat44();
    Mat44(const std::initializer_list<float>& l);

    inline void Fill(float t) { data_.fill(t); }

    float Get(const Point& p) const;
    void Set(const Point& p, const float& value);
    bool InMat(const Point& p) const;
    inline const float* Data() const { return data_.data(); }

protected:
    std::array<float, 4 * 4> data_;
};

inline double Radians(double degree) {
    return degree * M_PI / 180.0;
}

inline double Degress(double radians) {
    return radians * 180.0 / M_PI;
}

inline double Cross2D(const Point& v1, const Point& v2) {
    return v1.x * v2.y - v2.x * v1.y;
}

inline Mat44 CreateOrthoMat(float left, float right,
                            float bottom, float top,
                            float near, float far) {
    return Mat44({
            2.0f/(right - left), 0,                   0,                 (right + left)/(left - right),
            0,                   2.0f/(top - bottom), 0,                 (top + bottom)/(bottom - top),
            0,                   0,                   2.0f/(near - far), (near + far)/(far - near),
            0,                   0,                   0,                 1,
           });
}