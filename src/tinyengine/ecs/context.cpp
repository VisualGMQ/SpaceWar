#include "tinyengine/ecs/context.hpp"
#include "tinyengine/ecs/entity.hpp"

Pool<Entity>::ElemContainer& Context::GetEntities() {
    return entities_.GetElems();
}

void Context::DestroyEntity(Entity* entity) {
    for (size_t i = 0; i < ComponentIdx::GetCount(); i++) {
        if (entity->Has(i)) {
            DestroyComponentById(entity->Get(i), i);
        }
    }
    entities_.Destroy(entity);
}

int Context::GetEntityNum() const {
    return entities_.GetNum();
}

bool Context::HasEntity(Entity* entity) {
    auto& entities = entities_.GetElems();
    return std::find(entities.begin(), entities.end(), entity) !=
           entities.end();
}

Entity* Context::CreateEntity() {
    return entities_.Create(this);
}
