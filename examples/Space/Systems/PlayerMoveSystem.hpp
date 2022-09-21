#ifndef SPACE_ECS_PLAYER_MOVE_SYSTEM_HPP
#define SPACE_ECS_PLAYER_MOVE_SYSTEM_HPP

#include <Freyr/Core/BaseSystem.hpp>

#include "../Core/Time.hpp"
#include "../Core/Input.hpp"

struct TransformComponent;
struct RigidBodyComponent;
struct PlayerTag;

class PlayerMoveSystem : public freyr::BaseSystem {
public:
    using Signature = std::tuple<TransformComponent, RigidBodyComponent, PlayerTag>;

    PlayerMoveSystem() = default;

    ~PlayerMoveSystem() = default;

    void onUpdate() override;
private:
    freyr::EntityID createBoost(freyr::EntityID owner);
    freyr::EntityID placeBoost(freyr::EntityID owner, freyr::EntityID leftBoost, freyr::EntityID rightBoost);
};


#endif // SPACE_ECS_PLAYER_MOVE_SYSTEM_HPP
