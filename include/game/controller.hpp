#pragma once

class Controller {
public:
    virtual ~Controller() = default;

    virtual void Update(float dt) = 0;
};
