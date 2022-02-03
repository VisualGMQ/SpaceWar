#pragma once

#include "libmath.hpp"

class Camera final {
public:
    const Mat44& GetView() const { return viewMat_; }
    void Move(const Point& offset);
    void MoveTo(const Point& pos);
    /* scale screen in [1.0, 2.0] */
    void Scale(const Point& scale);
    bool TryCalcView();

private:
    Mat44 viewMat_;
    Point position_;
    Point scale_;
    bool dirty_ = false;
};
