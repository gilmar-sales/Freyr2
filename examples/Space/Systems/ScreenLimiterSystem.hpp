#pragma once

#include <Freyr/Core/BaseSystem.hpp>

struct TransformComponent;
struct RigidBodyComponent;
struct CircleColliderComponent;

class ScreenLimiterSystem: public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, CircleColliderComponent>;

    ScreenLimiterSystem()  = default;
    ~ScreenLimiterSystem() = default;

    void onUpdate() override;
};
