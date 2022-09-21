#include "CombatSystem.hpp"

#include "../World.hpp"

void CombatSystem::onReceive(CollisionEvent event)
{
    if(world->hasTag<BulletTag>(event.collisor))
    {
        if(world->hasTag<EnemyTag>(event.target))
        {
            world->destroyEntity(event.collisor);

            auto &bullet_comp = world->getComponent<BulletComponent>(event.collisor);
            world->getComponent<PlayerComponent>(bullet_comp.owner).score += 1;

            auto &collider  = world->getComponent<CircleColliderComponent>(event.target);
            float newRadius = collider.radius / 2.f;
            float newScale  = newRadius / 32.f;

            if(newRadius > 10)
            {
                auto &meteorTransform = world->getComponent<TransformComponent>(event.target);
                auto &meteorCollider  = world->getComponent<CircleColliderComponent>(event.target);

                meteorTransform.scale = {newScale, newScale, newScale};
                meteorCollider.radius = newRadius;
            }
            else
            {
                world->destroyEntity(event.target);
            }
        }
    }
    else if(world->hasTag<PlayerTag>(event.collisor))
    {
        if(world->hasTag<EnemyTag>(event.target))
        {
            world->destroyEntity(event.target);

            auto &life = world->getComponent<PlayerComponent>(event.collisor);
            life.lifes -= 1;
        }
    }
}
