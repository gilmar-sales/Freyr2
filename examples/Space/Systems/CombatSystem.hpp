#ifndef FREYR_COMBATSYSTEM_HPP
#define FREYR_COMBATSYSTEM_HPP

#include <Freyr/Core/BaseSystem.hpp>

struct RigidBodyComponent;
struct CircleColliderComponent;

#include "../Events/GameEvents.hpp"

class CombatSystem : public freyr::BaseSystem {
public:
    using Signature = std::tuple<CircleColliderComponent, RigidBodyComponent>;

    CombatSystem() = default;

    ~CombatSystem() = default;

    void onReceive(CollisionEvent event);
};


#endif //FREYR_COMBATSYSTEM_HPP
