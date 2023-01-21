#include "PhysicsSystem.hpp"

#include "../Core/Application.hpp"

#include <execution>

void PhysicsSystem::onUpdate()
{
    std::for_each(
        std::execution::par, getRegisteredEntities().begin(), getRegisteredEntities().end(), [&](auto entity) {
            auto [transform, rigidbody] = world->getComponents<TransformComponent, RigidBodyComponent>(entity);

            transform.position += rigidbody.velocity * Time::DeltaTime;

            rigidbody.velocity /= 1 + rigidbody.mass * Time::DeltaTime;
        });
}
