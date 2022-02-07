#pragma once

#include "entity.hpp"
#include "tinyengine/tinyengine.hpp"

class System {
public:
    virtual ~System() = default;

    bool IsWorking() const { return active_; }
    void StartWork() { active_ = true; }
    void StopWork() { active_ = false; }

private:
    bool active_ = true;
};

class UpdateSystem: public System {
public:
    virtual ~UpdateSystem() = default;

    virtual void Update(float dt) = 0;
};

class RenderSystem: public System {
public:
    virtual ~RenderSystem() = default;

    virtual void Render() = 0;
};


class SystemManager final {
public:
    void AddUpdateSystem(UpdateSystem* system) { updateSystems_.emplace_back(system); }
    void AddRenderSystem(RenderSystem* system) { renderSystems_.emplace_back(system); }

    void Update(float dt);
    void Render();

    void Clear() { ClearUpdateSystems(); ClearRenderSystems(); }
    void ClearUpdateSystems() { updateSystems_.clear(); }
    void ClearRenderSystems() { renderSystems_.clear(); }

private:
    std::vector<Ref<UpdateSystem>> updateSystems_;
    std::vector<Ref<RenderSystem>> renderSystems_;
};
