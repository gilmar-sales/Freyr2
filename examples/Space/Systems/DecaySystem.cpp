#include "DecaySystem.hpp"
#include "../World.hpp"

void DecaySystem::onUpdate() {
        for (auto entity : getRegisteredEntities()) {
            auto &decay = world->getComponent<DecayComponent>(entity);
            decay.current += Time::DeltaTime;

            if (decay.current > decay.maxTime) {
                decay.current = 0.f;
                decay.maxTime = 0.f;
                world->destroyEntity(entity);
//                std::cout << "Decay entity(" << entity << ") - " << world->entities().getSignature(entity) << std::endl;
            }
        }
}

