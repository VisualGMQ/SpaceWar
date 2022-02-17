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

void BulletUpdateSystem::Update(float dt) {
    for (auto& bullet : Bullets) {
        if (bullet->Get<BulletCmpt>()->type == BulletCmpt::Missile) {
            updateMissile(dt,
                          *bullet->Use<BulletCmpt>(),
                          *bullet->Use<MoveCmpt>(),
                          *bullet->Use<MotionCmpt>());
        }
        updateBulletLife(dt, *bullet->Use<BulletCmpt>());
    }
}

void BulletUpdateSystem::updateMissile(float dt,
                                        BulletCmpt& bullet,
                                        MoveCmpt& move,
                                        MotionCmpt& motion) {
    if (bullet.target) {
        if (!bullet.target->IsAlive()) {
            bullet.target = nullptr;
        } else {
            Point v = bullet.target->Get<MoveCmpt>()->position - move.position;
            float cross = Cross(Rotate(Point{0, -1}, bullet.rotation), v);
            if (cross > 0) {
                bullet.rotation += MissileRotateDegree * dt;
            } else {
                bullet.rotation -= MissileRotateDegree * dt;
            }
            Point dir = Rotate(Point{0, -1}, bullet.rotation);
            motion.speed = dir * Len(motion.speed);
        }
    }
}

void BulletUpdateSystem::updateBulletLife(float dt, BulletCmpt& bullet) {
    bullet.liveTime += dt;
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
                entity->Has<GroupCmpt>() &&
                bullet->Get<GroupCmpt>()->groupIdx != entity->Get<GroupCmpt>()->groupIdx &&
                IsRectsIntersect(bullet->Get<CollisionCmpt>()->rect,
                                 entity->Get<CollisionCmpt>()->rect)) {
                if (entity->Has<LifeCmpt>()) {
                    entity->Use<LifeCmpt>()->hp -= bullet->Get<BulletCmpt>()->damage;
                    Sounds["hurt"]->Play();
                }
                bullet->Use<BulletCmpt>()->alive = false;
            }
        }
    }
}

void CleanupSystem::Update(float dt) {
    auto destroyFunc = [&](const EntityPtr& entity){
        ECSContext.DestroyEntity(entity);
    };

    for (int i = 0; i < InitInfo.groupNum; i++) {
        Groups[i].RemoveAll([](const EntityPtr& entity){
            if (entity->Has<LifeCmpt>() &&
                entity->Get<LifeCmpt>()->hp <= 0) {
                return true;
            } else {
                return false;
            }
        });
    }

    Bullets.RemoveAll([](const EntityPtr& entity){
        return !entity->Get<BulletCmpt>()->alive ||
               entity->Get<BulletCmpt>()->liveTime >= BulletDieTime;
    }, destroyFunc);

    Entities.RemoveAll([&](const EntityPtr& entity){
        if (entity->Has<LifeCmpt>() &&
            entity->Get<LifeCmpt>()->hp <= 0) {
            Sounds["explosion"]->Play();
            return true;
        } else {
            return false;
        }
    }, destroyFunc);

}

void WeaponCooldownSystem::Update(float dt) {
    for (auto& entity : Entities) {
        if (entity->Has<FreightShipCmpt>()) {
            auto weapon = entity->Use<FreightShipCmpt>()->weapon;
            coolDown(*weapon, dt);
        }
        if (entity->Has<FightShipCmpt>()) {
            auto fightShip = entity->Use<FightShipCmpt>();
            coolDown(*fightShip->weapon1, dt);
            coolDown(*fightShip->weapon2, dt);
        }
    }
}

void WeaponCooldownSystem::coolDown(SpaceshipWeaponCmpt& weapon, float dt) {
    if (weapon.coolDown >= 0) {
        weapon.coolDown -= dt;
    }
}

void RenderEntitySystem::Render() {
    for (auto& entity: Entities) {
        if (entity->Has<RenderCmpt>()) {
            float rotation = 0;
            if (entity->Has<FightShipCmpt>()) {
                rotation = entity->Get<FightShipCmpt>()->degree;
            }
            Color color = {1, 1, 1, 1};
            if (entity->Has<GroupCmpt>()) {
                color = GroupSpecColor[entity->Get<GroupCmpt>()->groupIdx];
            }
            renderEntity(entity, *entity->Get<RenderCmpt>(), rotation, color);
            // renderCollideBox(entity);
        }
    }

    for (auto& bullet: Bullets) {
        float rotation = 0;
        if (bullet->Get<BulletCmpt>()->type == BulletCmpt::Missile) {
            rotation = bullet->Get<BulletCmpt>()->rotation;
        }
        renderEntity(bullet, *bullet->Get<RenderCmpt>(), rotation, Color{1, 1, 1, 1});
        // renderCollideBox(bullet);
    }
}

void RenderEntitySystem::renderCollideBox(Entity* entity) {
    if (entity && entity->Has<CollisionCmpt>()) {
        Renderer::SetDrawColor(Color{0, 255, 0, 255});
        Renderer::DrawRect(entity->Get<CollisionCmpt>()->rect);
    }
}

void RenderEntitySystem::renderEntity(Entity* entity,
                                      const RenderCmpt& renderCmpt,
                                      float rotation,
                                      const Color& color) {
    if (entity->Has<MoveCmpt>()) {
        auto& pos = entity->Get<MoveCmpt>()->position;
        if (renderCmpt.type == RenderCmpt::TypeTexture) {
            Renderer::DrawTexture(renderCmpt.texture,
                                  nullptr,
                                  pos,
                                  Size{EntityRenderSize, EntityRenderSize},
                                  rotation,
                                  Renderer::NoFlip,
                                  color);
        } else {
            Renderer::DrawTile(renderCmpt.tile,
                               pos,
                               Size{EntityRenderSize, EntityRenderSize},
                               rotation,
                               Renderer::NoFlip,
                               color);
        }
    }
}

void EnergyProductSystem::Update(float dt) {
    for (auto& entity: Entities) {
        if (entity->Has<EnergyProductCmpt>()) {
            coolDown(*entity->Use<EnergyProductCmpt>(), dt);
        }
    }
}

void EnergyProductSystem::coolDown(EnergyProductCmpt& cmpt, float dt) {
    if (cmpt.IsCoolDowning()) {
        cmpt.cooldown -= dt;
    } else {
        cmpt.cooldown = cmpt.duration;
        cmpt.amount += cmpt.productAmount;
    }
}

void AIUpdateSystem::Update(float) {
    for (auto& entity : Entities) {
        if (entity->Has<AICmpt>()) {
            auto func = entity->Get<AICmpt>()->func;
            if (func) {
                func(entity);
            }
        }
    }
}
