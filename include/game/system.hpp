#pragma once

#include "tinyengine/ecs/system.hpp"
#include "tinyengine/tinyengine.hpp"
#include "game/global.hpp"
#include "game/component.hpp"
#include "game/entity.hpp"

class PhysicalSystem: public UpdateSystem {
public:
    void Update(float dt) override;

private:
    void physicalStep(Entity* entity, float dt, MoveCmpt&, MotionCmpt&);
};

class ColliRectCorrectSystem: public UpdateSystem {
public:
    void Update(float dt) override;

private:
    void correctColliRect(MoveCmpt&, CollisionCmpt&);
};

class CollideSystem: public UpdateSystem {
public:
    void Update(float dt) override;
};

class CleanupSystem: public UpdateSystem {
public:
    void Update(float dt) override;
};

class BulletCooldownSystem: public UpdateSystem {
public:
    void Update(float dt) override;
};

class RenderEntitySystem: public RenderSystem {
public:
    void Render() override;

private:
    void renderEntity(Entity* entity, const RenderCmpt&);
    void renderCollideBox(Entity* entity);
};
