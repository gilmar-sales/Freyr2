#include "PlayerSystem.hpp"

#include "../World.hpp"

void PlayerSystem::onUpdate()
{
    for (auto entity : getRegisteredEntities())
    {
        auto [transform, player] = world->getComponents<TransformComponent, PlayerComponent>(entity);

        if (player.lifes <= 0)
        {
            notify(PlayerEndGameEvent{});
            transform.position = {0.f, 0.f, 0.f};
            player.lifes       = 4;
            player.score       = 0;
        }
    }
}
