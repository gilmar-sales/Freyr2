#include "CollisionSystem.hpp"

#include "../Core/Application.hpp"
#include "../World.hpp"

#include <execution>

void CollisionSystem::onUpdate()
{
    float halfWidth = Application::Get().getWindow().getWidth() * 0.5f;
    auto quadtree   = QuadTree(glm::vec2(0, 0), halfWidth, 4);

    for (auto entity : getRegisteredEntities())
    {
        auto [transform, collider] = world->getComponents<TransformComponent, CircleColliderComponent>(entity);

        quadtree.insert({.id       = entity,
                          .position = glm::vec2(transform.position.x, transform.position.y),
                          .radius   = collider.radius});
    }

    std::for_each(std::execution::par, getRegisteredEntities().begin(), getRegisteredEntities().end(),
                  [&](auto entity) {
                      auto [transform, rigidbody, collider] =
                          world->getComponents<TransformComponent, RigidBodyComponent, CircleColliderComponent>(entity);

                      std::vector<ColliderData> collisions = std::vector<ColliderData>();

                      ColliderData collisor = {.id       = entity,
                                               .position = glm::vec2(transform.position.x, transform.position.y),
                                               .radius   = collider.radius * collider.scale};

                      quadtree.query(collisor, &collisions);

                      for (auto &collision : collisions)
                      {
                          notify(CollisionEvent{.collisor = collisor.id, .target = collision.id});
                      }
                  });
}
