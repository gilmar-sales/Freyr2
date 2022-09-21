#include "PhysicsSystem.hpp"

#include "../Core/Application.hpp"

void PhysicsSystem::onUpdate()
{
    for(auto entity: getRegisteredEntities())
    {
        auto &transform = world->getComponent<TransformComponent>(entity);
        auto &rigidbody = world->getComponent<RigidBodyComponent>(entity);
        auto &collider  = world->getComponent<CircleColliderComponent>(entity);

        transform.position += rigidbody.velocity * Time::DeltaTime;

        rigidbody.velocity /= 1 + rigidbody.mass * Time::DeltaTime;

        float halfWidth  = (float)Application::Get().getWindow().getWidth() * 0.5f;
        float halfHeight = (float)Application::Get().getWindow().getHeight() * 0.5f;

        if(world->hasTag<EnemyTag>(entity))
        {
            auto radius = collider.radius * collider.scale * transform.scale.x;

            if(transform.position.x > halfWidth - radius)
            {
                rigidbody.velocity.x *= -1;
                transform.position.x = halfWidth - radius;
            }
            else if(transform.position.x < -halfWidth + radius)
            {
                rigidbody.velocity.x *= -1;
                transform.position.x = -halfWidth + radius;
            }

            if(transform.position.y > halfHeight - radius)
            {
                rigidbody.velocity.y *= -1;
                transform.position.y = halfHeight - radius;
            }
            else if(transform.position.y < -halfHeight + radius)
            {
                rigidbody.velocity.y *= -1;
                transform.position.y = -halfHeight + radius;
            }
        }
        else if(world->hasTag<PlayerTag>(entity))
        {
            if(transform.position.x > halfWidth)
            {
                transform.position.x = -halfWidth;
            }
            else if(transform.position.x < -halfWidth)
            {
                transform.position.x = halfWidth;
            }

            if(transform.position.y > halfHeight)
            {
                transform.position.y = -halfHeight;
            }
            else if(transform.position.y < -halfHeight)
            {
                transform.position.y = halfHeight;
            }
        }
    }
}
