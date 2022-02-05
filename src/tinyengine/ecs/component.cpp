#include "ecs/component.hpp"
#include "ecs/context.hpp"

ComponentId ComponentIdx::count_ = 0;

std::unordered_map<ComponentId, Pool<Component>> gComponentPool;
