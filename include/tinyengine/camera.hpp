#pragma once

#include "libmath.hpp"

class Camera final {
public:
    const Mat44& GetView() const { return viewMat_; }
    void Move(const Point& offset);
    void MoveTo(const Point& pos);
    /* scale screen in [1.0, 2.0] */
    void Scale(const Point& scale);
    void SetAnchor(const Point& anchor);
    bool TryCalcView();
    const Point& GetPosition() const { return position_; }

private:
    Mat44 viewMat_;
    Point position_ = {0, 0};
    Point scale_ = {1, 1};
    Point anchor_ = {0, 0};
    bool dirty_ = true;
};
