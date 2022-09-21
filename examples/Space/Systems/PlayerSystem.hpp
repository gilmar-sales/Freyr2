//
// Created by gilma on 22/12/2021.
//

#ifndef SPACE_ECS_PLAYER_SYSTEM_HPP
#define SPACE_ECS_PLAYER_SYSTEM_HPP

#include <iostream>
#include <tuple>

#include <Freyr/Core/PublisherSystem.hpp>

#include "../Core/Time.hpp"
#include "../Core/Input.hpp"

#include "../Components/PlayerComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Tags/PlayerTag.hpp"
#include "../Events/GameEvents.hpp"

class MeteorManagerSystem;

class PlayerSystem : public freyr::PublisherSystem<MeteorManagerSystem> {
public:
    using Signature = std::tuple<PlayerTag, PlayerComponent, TransformComponent>;

    PlayerSystem() = default;

    ~PlayerSystem() = default;

    void onUpdate() override;
};


#endif //SPACE_ECS_PLAYER_SYSTEM_HPP
