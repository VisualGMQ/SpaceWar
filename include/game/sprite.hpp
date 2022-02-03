#pragma once

#include "tinyengine/pch.hpp"
#include "tinyengine/libmath.hpp"

class Sprite {
public:
    virtual ~Sprite() = default;

    void Move(const Point& offset) { position_ += offset; dirty_ = true; }
    void MoveTo(const Point& p) { position_ = p; dirty_ = true; }
    void Rotate(const float degreeDelta) { rotation_ += degreeDelta; dirty_ = true; }
    void RotateTo(const float degree) { rotation_ = degree; dirty_ = true; }

    bool TryCalcView();
    const Mat44& GetModel() const { return modelMat_; }

    virtual void Update() { oldPosition_ = position_; }

private:
    Point position_ = {0, 0};
    Point oldPosition_;
    float rotation_ = 0;
    bool dirty_ = false;
    Mat44 modelMat_;
};
