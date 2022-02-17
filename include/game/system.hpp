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

class MissileUpdateSystem: public UpdateSystem {
public:
    void Update(float dt) override;

private:
    void updateMissile(float dt, BulletCmpt&, MoveCmpt&, MotionCmpt&);
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

class WeaponCooldownSystem: public UpdateSystem {
public:
    void Update(float dt) override;

private:
    void coolDown(SpaceshipWeaponCmpt& weapon, float dt);
};

class RenderEntitySystem: public RenderSystem {
public:
    void Render() override;

private:
    void renderEntity(Entity* entity, const RenderCmpt&, float rotation, const Color&);
    void renderCollideBox(Entity* entity);
};

class EnergyProductSystem: public UpdateSystem {
public:
    void Update(float) override;

private:
    void coolDown(EnergyProductCmpt& cmpt, float dt);
};

class AIUpdateSystem: public UpdateSystem {
public:
    void Update(float) override;
};
