#pragma once

#include <Freyr/Core/BaseSystem.hpp>
#include <Freyr/Types/Entity.hpp>

#include "../Core/Input.hpp"
#include "../Core/TextureManager.hpp"
#include "../Core/Time.hpp"

struct TransformComponent;
struct RigidBodyComponent;
struct LaserGunComponent;

class ShootSystem: public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, LaserGunComponent>;

    ShootSystem() = default;

    ~ShootSystem() = default;

    void onUpdate() override;

    freyr::EntityID createBullet(freyr::EntityID owner);
};
