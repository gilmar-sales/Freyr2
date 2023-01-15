#include "ScreenLimiterSystem.hpp"

#include "../Core/Application.hpp"

void ScreenLimiterSystem::onUpdate()
{
    for(auto entity: getRegisteredEntities())
    {
        auto [transform, rigidbody, collider] =
            world->getComponents<TransformComponent, RigidBodyComponent, CircleColliderComponent>(entity);

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