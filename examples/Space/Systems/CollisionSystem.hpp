#pragma once

#include <Freyr/Core/PublisherSystem.hpp>

#include "../Core/Time.hpp"
#include "../Utils/quadtree.hpp"

class Application;

struct TransformComponent;
struct RigidBodyComponent;
struct CircleColliderComponent;
class CombatSystem;

class CollisionSystem: public freyr::PublisherSystem<CombatSystem>
{
  public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, CircleColliderComponent>;

    CollisionSystem() = default;

    ~CollisionSystem() = default;

    void onUpdate() override;
};
