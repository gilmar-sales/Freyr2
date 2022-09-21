#include "DecaySystem.hpp"

#include "../Core/Time.hpp"
#include "../World.hpp"

void DecaySystem::onUpdate()
{
    for(auto entity: getRegisteredEntities())
    {
        auto &decay = world->getComponent<DecayComponent>(entity);
        decay.current += Time::DeltaTime;

        if(decay.current > decay.maxTime)
        {
            decay.current = 0.f;
            decay.maxTime = 0.f;
            world->destroyEntity(entity);
        }
    }
}
