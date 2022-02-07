#include "tinyengine/ecs/system.hpp"

void SystemManager::Update(float dt) {
    for (auto& system: updateSystems_) {
        if (system->IsWorking()) {
            system->Update(dt);
        }
    }
}

void SystemManager::Render() {
    for (auto& system: renderSystems_) {
        if (system->IsWorking()) {
            system->Render();
        }
    }
}
