#include "game/system.hpp"

void PhysicalSystem::Update(float dt) {
    for (auto& entity: Entities) {
        if (entity->Has<MoveCmpt>() && entity->Has<MotionCmpt>()) {
            // update entities
            physicalStep(entity, dt,
                         *entity->Use<MoveCmpt>(),
                         *entity->Use<MotionCmpt>());

            // update bullets
            for (auto& bullet : Bullets) {
                if (bullet->Has<MoveCmpt>() && bullet->Has<MotionCmpt>()) {
                    physicalStep(bullet, dt,
                                 *bullet->Use<MoveCmpt>(),
                                 *bullet->Use<MotionCmpt>());
                }
            }

        }
    }
}

void PhysicalSystem::physicalStep(Entity* entity,
                                  float dt,
                                  MoveCmpt& moveCmpt,
                                  MotionCmpt& motionCmpt) {
    moveCmpt.oldPosition = moveCmpt.position;

    motionCmpt.speed += motionCmpt.acceleration * dt;
    if (Len(motionCmpt.speed) > motionCmpt.maxSpeed) {
        motionCmpt.speed = Normalize(motionCmpt.speed) * motionCmpt.maxSpeed;
    }

    moveCmpt.position += motionCmpt.speed * dt + 0.5 * motionCmpt.acceleration * dt * dt;

    motionCmpt.acceleration = Point{0, 0};
}

void ColliRectCorrectSystem::Update(float dt) {
    for (auto& entity: Entities) {
        if (entity->Has<CollisionCmpt>() &&
            entity->Has<MoveCmpt>()) {
            correctColliRect(*entity->Use<MoveCmpt>(),
                             *entity->Use<CollisionCmpt>());
        }
    }
}

void ColliRectCorrectSystem::correctColliRect(MoveCmpt& move, CollisionCmpt& collision) {
    collision.rect.x = move.position.x;
    collision.rect.y = move.position.y;
}

void CleanupSystem::Update(float dt) {
    using EntityPtr = Entity*;
    Bullets.RemoveAll([](const EntityPtr& entity){
        return !IsPointInRect(entity->Get<MoveCmpt>()->position,
                              Rect{0, 0, GameWindowWidth, GameWindowHeight});
    });
}

void BulletCooldownSystem::Update(float dt) {
    for (auto& entity : Entities) {
        if (entity->Has<SpaceshipWeaponCmpt>()) {
            auto weapon = entity->Use<SpaceshipWeaponCmpt>();
            if (weapon->coolDown >= 0) {
                weapon->coolDown -= dt;
            }
        }
    }
}

void RenderEntitySystem::Render() {
    for (auto& entity: Entities) {
        if (entity->Has<RenderCmpt>()) {
            renderEntity(entity, *entity->Get<RenderCmpt>());
        }
    }
    
    for (auto& bullet: Bullets) {
        renderEntity(bullet, *bullet->Get<RenderCmpt>());
    }
}

void RenderEntitySystem::renderEntity(Entity* entity, const RenderCmpt& renderCmpt) {
    if (entity->Has<MoveCmpt>()) {
        auto& pos = entity->Get<MoveCmpt>()->position;
        if (renderCmpt.type == RenderCmpt::TypeTexture) {
            Renderer::DrawTexture(renderCmpt.texture,
                                  nullptr,
                                  pos);
        } else {
            Renderer::DrawTile(renderCmpt.tile,
                               pos);
        }
    }
}
