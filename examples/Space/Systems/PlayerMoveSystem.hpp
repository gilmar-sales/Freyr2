#pragma once

#include <Freyr/Core/BaseSystem.hpp>

#include "../Core/Input.hpp"
#include "../Core/Time.hpp"

struct TransformComponent;
struct RigidBodyComponent;
struct PlayerTag;

class PlayerMoveSystem: public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, PlayerTag>;

    PlayerMoveSystem() = default;

    ~PlayerMoveSystem() = default;

    void onUpdate() override;

  private:
    freyr::EntityID createBoost(freyr::EntityID owner);
    freyr::EntityID placeBoost(freyr::EntityID owner, freyr::EntityID leftBoost, freyr::EntityID rightBoost);
};
