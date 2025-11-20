#pragma once

#include <FreyrCT/Core/BaseSystem.hpp>
#include <FreyrCT/Types/Entity.hpp>

#include "../Events/InputEvents.hpp"

struct TransformComponent;
struct RigidBodyComponent;
struct LaserGunComponent;

class ShootSystem : public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, LaserGunComponent>;

    ShootSystem() = default;

    ~ShootSystem() = default;

    void onReceive(const KeyDownEvent &event);

    freyr::EntityID createBullet(freyr::EntityID owner);
};
