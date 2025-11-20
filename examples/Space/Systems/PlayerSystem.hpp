#pragma once

#include <FreyrCT/Core/PublisherSystem.hpp>

#include "../Components/PlayerComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Core/Time.hpp"
#include "../Events/GameEvents.hpp"
#include "../Tags/PlayerTag.hpp"

class MeteorManagerSystem;

class PlayerSystem: public freyr::PublisherSystem<MeteorManagerSystem>
{
  public:
    using Signature = std::tuple<PlayerTag, PlayerComponent, TransformComponent>;

    PlayerSystem() = default;

    ~PlayerSystem() = default;

    void onUpdate() override;
};
