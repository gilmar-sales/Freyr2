#pragma once

#include <FreyrCT/Core/BaseSystem.hpp>

struct TransformComponent;
struct RigidBodyComponent;
struct PlayerTag;
struct KeyPressedEvent;

class PlayerMoveSystem : public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, PlayerTag>;

    PlayerMoveSystem() = default;

    ~PlayerMoveSystem() = default;

    void onUpdate() override;

    void onReceive(const KeyPressedEvent &event);

  private:
    freyr::EntityID createBoost(freyr::EntityID owner);
    freyr::EntityID placeBoost(freyr::EntityID owner, freyr::EntityID leftBoost, freyr::EntityID rightBoost);

    float m_velocity     = 0;
    float m_turnVelocity = 0;
};
