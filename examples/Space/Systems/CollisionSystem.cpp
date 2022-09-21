#include "CollisionSystem.hpp"
#include "../World.hpp"
#include "../Core/Application.hpp"

void CollisionSystem::onUpdate() {
    float halfWidth = (float) Application::Get().getWindow().getWidth() * 0.5f;
    QuadTree quadtree = QuadTree(glm::vec2(0, 0), halfWidth, 4);

    for (auto entity: getRegisteredEntities()) {
        auto &transform = world->getComponent<TransformComponent>(entity);
        auto &collider = world->getComponent<CircleColliderComponent>(entity);
        quadtree.insert({entity, glm::vec2(transform.position.x, transform.position.y), collider.radius});
    }

    for (auto entity: getRegisteredEntities()) {
        auto &transform = world->getComponent<TransformComponent>(entity);
        auto &rigidbody = world->getComponent<RigidBodyComponent>(entity);
        auto &collider = world->getComponent<CircleColliderComponent>(entity);

        Entity ent = {entity, glm::vec2(transform.position.x, transform.position.y), collider.radius * collider.scale};
        std::vector<Entity> collisions = std::vector<Entity>();
        quadtree.query(ent, &collisions);

        for(auto& collision : collisions) {
            notify(world, CollisionEvent{.collisor = entity, .target = collision.id});
        }
    }
}

