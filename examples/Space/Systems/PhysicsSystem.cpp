#include "PhysicsSystem.hpp"

#include "../Core/Application.hpp"

void PhysicsSystem::onUpdate()
{
    for(auto entity: getRegisteredEntities())
    {
        auto [transform, rigidbody] = world->getComponents<TransformComponent, RigidBodyComponent>(entity);

        transform.position += rigidbody.velocity * Time::DeltaTime;

        rigidbody.velocity /= 1 + rigidbody.mass * Time::DeltaTime;
    }
}
