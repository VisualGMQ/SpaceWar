#include "camera.hpp"

bool Camera::TryCalcView() {
    if (dirty_) {
        viewMat_ = Mat44({
                    scale_.x,        0, 0, -position_.x,
                           0, scale_.y, 0, -position_.y,
                           0,        0, 1,            0,
                           0,        0, 0,            1,
                });
        dirty_ = false;
        return true;
    } else {
        return false;
    }
}

void Camera::Move(const Point& offset) {
    position_ += offset;
    dirty_ = true;
}

void Camera::MoveTo(const Point& pos) {
    position_ = pos;
    dirty_ = true;
}

void Camera::Scale(const Point& scale) {
    scale_.x = Clamp(1.0f, 2.0f, scale.x);
    scale_.y = Clamp(1.0f, 2.0f, scale.y);
    dirty_ = true;
}
