#pragma once

class Scence {
public:
    virtual ~Scence() = default;

    virtual void OnInit() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnQuit() {}
};
