#ifndef SPACE_ECS_SHOOT_SYSTEM_HPP
#define SPACE_ECS_SHOOT_SYSTEM_HPP

#include <iostream>

#include <Freyr/Types/Entity.hpp>
#include <Freyr/Core/BaseSystem.hpp>

#include "../Core/Time.hpp"
#include "../Core/Input.hpp"
#include "../Core/TextureManager.hpp"

struct TransformComponent;
struct RigidBodyComponent;
struct LaserGunComponent;

class ShootSystem : public freyr::BaseSystem {
public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, LaserGunComponent>;

    ShootSystem() = default;

    ~ShootSystem() = default;

    void onUpdate() override;

    freyr::EntityID createBullet(freyr::EntityID owner);
};

#endif // SPACE_ECS_SHOOT_SYSTEM_HPP
