#include "DecaySystem.hpp"

#include "../Core/Time.hpp"
#include "../World.hpp"

void DecaySystem::onUpdate()
{
    for (auto entity : getRegisteredEntities())
    {
        auto &decay = world->getComponent<DecayComponent>(entity);
        decay.currentTime += Time::DeltaTime;

        if (decay.currentTime > decay.maxTime)
        {
            decay = {};
            world->destroyEntity(entity);
        }
    }
}
