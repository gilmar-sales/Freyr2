#include "DecaySystem.hpp"

#include "../Core/Time.hpp"
#include "../World.hpp"

#include <execution>
#include <mutex>

void DecaySystem::onUpdate()
{
    std::for_each(std::execution::par, getRegisteredEntities().begin(), getRegisteredEntities().end(),
                  [&](auto entity) {
                      auto &decay = world->getComponent<DecayComponent>(entity);
                      decay.currentTime += Time::DeltaTime;

                      if (decay.currentTime > decay.maxTime)
                      {
                          decay = {};
                          world->destroyEntity(entity);
                      }
                  });
}
