#pragma once

#include "../Meta/Iteration.hpp"
#include "BaseSystem.hpp"

FREYR_BEGIN

template<typename... Subscribers>
class PublisherSystem: public BaseSystem
{
  public:
    template<typename Event>
    void notify(auto *world, Event event)
    {
        meta::forList(
            [this, world, event](auto system) { world->systems().template notify<decltype(system), Event>(event); },
            std::tuple<Subscribers...>{});
    }
};

FREYR_END
