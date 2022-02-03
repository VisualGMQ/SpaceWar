#include "game/sprite.hpp"

bool Sprite::TryCalcView() {
    if (dirty_) {
        float theta = Radians(rotation_);
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);
        modelMat_ = Mat44({
                        cosTheta, -sinTheta, 0, position_.x,
                        sinTheta,  cosTheta, 0, position_.y,
                               0,         0, 1,           0,
                               0,         0, 0,           1,
                    });
        dirty_ = false;
        return true;
    } else {
        return false;
    }
}
