#pragma once

#include <FreyrCT/Core/BaseSystem.hpp>

struct RigidBodyComponent;
struct CircleColliderComponent;

#include "../Events/GameEvents.hpp"

class CombatSystem: public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<CircleColliderComponent, RigidBodyComponent>;

    CombatSystem() = default;

    ~CombatSystem() = default;

    void onReceive(CollisionEvent event);
};
