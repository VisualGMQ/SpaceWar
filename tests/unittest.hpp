#pragma once

#include "tinyengine/libmath.hpp"
#include "tinyengine/tool.hpp"

#define TEST_TRUE(condition) do { \
    if (!(condition)) { \
        std::cout << "[TEST_TRUE] " << #condition << " test failed!" << std::endl; \
        FATAL_ERROR("TEST TRUE failed"); \
    } \
} while(0)

#define TEST_FALSE(condition) do { \
    if (condition) { \
        std::cout << "[TEST FALSE] " << #condition << " test failed!" << std::endl; \
        FATAL_ERROR("TEST FALSE failed"); \
    } \
} while(0)

inline Mat44 CreateTextureTransform(const Size& size, const Point& pos) {
    return Mat44({
                size.w, 0, 0, pos.x,
                0, size.h, 0, pos.y,
                0, 0, 1,     0,
                0, 0, 0,     1,
           });
}
