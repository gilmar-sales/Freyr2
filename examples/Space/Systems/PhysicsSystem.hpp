#ifndef SPACE_ECS_PHYSICS_SYSTEM_HPP
#define SPACE_ECS_PHYSICS_SYSTEM_HPP

#include <Freyr/Core/BaseSystem.hpp>

#include "../Core/Time.hpp"

struct TransformComponent;
struct RigidBodyComponent;

class Application;

class PhysicsSystem : public freyr::BaseSystem {
public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent>;

    PhysicsSystem() = default;

    ~PhysicsSystem() = default;

    void onUpdate() override;
};

#endif // SPACE_ECS_PHYSICS_SYSTEM_HPP
