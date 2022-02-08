#include "game/system.hpp"

void PhysicalSystem::Update(float dt) {
    // update entities
    for (auto& entity: Entities) {
        if (entity->Has<MoveCmpt, MotionCmpt>()) {
            physicalStep(entity, dt,
                         *entity->Use<MoveCmpt>(),
                         *entity->Use<MotionCmpt>());

        }
    }
    
    // update bullets
    for (auto& bullet : Bullets) {
        if (bullet->Has<MoveCmpt, MotionCmpt>()) {
            physicalStep(bullet, dt,
                         *bullet->Use<MoveCmpt>(),
                         *bullet->Use<MotionCmpt>());
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
        if (entity->Has<CollisionCmpt, MoveCmpt>()) {
            correctColliRect(*entity->Use<MoveCmpt>(),
                             *entity->Use<CollisionCmpt>());
        }
    }
    for (auto& bullets: Bullets) {
        if (bullets->Has<CollisionCmpt, MoveCmpt>()) {
            correctColliRect(*bullets->Use<MoveCmpt>(),
                             *bullets->Use<CollisionCmpt>());
        }
    }
}

void ColliRectCorrectSystem::correctColliRect(MoveCmpt& move, CollisionCmpt& collision) {
    collision.rect.x = move.position.x - collision.rect.w / 2;
    collision.rect.y = move.position.y - collision.rect.h / 2;
}

void CollideSystem::Update(float dt) {
    for (auto& bullet : Bullets) {
        for (auto& entity: Entities) {
            if (entity->Has<CollisionCmpt>() &&
                bullet->Get<BulletCmpt>()->owner != entity &&
                IsRectsIntersect(bullet->Get<CollisionCmpt>()->rect,
                                 entity->Get<CollisionCmpt>()->rect)) {
                if (entity->Has<LifeCmpt>()) {
                    entity->Use<LifeCmpt>()->hp -= bullet->Get<BulletCmpt>()->damage;
                }
                bullet->Use<BulletCmpt>()->alive = false;
            }
        }
    }
}

void CleanupSystem::Update(float dt) {
    using EntityPtr = Entity*;
    Bullets.RemoveAll([](const EntityPtr& entity){
        return !entity->Get<BulletCmpt>()->alive || !IsPointInRect(entity->Get<MoveCmpt>()->position,
                              Rect{0, 0, GameWindowWidth, GameWindowHeight});
    });
    Entities.RemoveAll([](const EntityPtr& entity){
        if (entity->Has<LifeCmpt>() &&
            entity->Get<LifeCmpt>()->hp <= 0) {
            return true;
        } else {
            return false;
        }
    },
    [&](const EntityPtr& entity){
        ECSContext.DestroyEntity(entity);
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
            renderCollideBox(entity);
        }
    }
    
    for (auto& bullet: Bullets) {
        renderEntity(bullet, *bullet->Get<RenderCmpt>());
        renderCollideBox(bullet);
    }
}

void RenderEntitySystem::renderCollideBox(Entity* entity) {
    if (entity && entity->Has<CollisionCmpt>()) {
        Renderer::SetDrawColor(Color{0, 255, 0, 255});
        Renderer::DrawRect(entity->Get<CollisionCmpt>()->rect);
    }
}

void RenderEntitySystem::renderEntity(Entity* entity, const RenderCmpt& renderCmpt) {
    if (entity->Has<MoveCmpt>()) {
        auto& pos = entity->Get<MoveCmpt>()->position;
        float degree = 0;
        if (entity->Has<FightShipCmpt>()) {
            degree = entity->Get<FightShipCmpt>()->degree;
        }
        if (renderCmpt.type == RenderCmpt::TypeTexture) {
            Renderer::DrawTexture(renderCmpt.texture,
                                  nullptr,
                                  pos,
                                  Size{0, 0},
                                  degree);
        } else {
            Renderer::DrawTile(renderCmpt.tile,
                               pos,
                               Size{0, 0},
                               degree);
        }
    }
}
