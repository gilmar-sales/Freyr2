#include "PlayerSystem.hpp"

#include "../World.hpp"

void PlayerSystem::onUpdate()
{
    for(auto entity: getRegisteredEntities())
    {
        auto &transform = world->getComponent<TransformComponent>(entity);
        auto &player    = world->getComponent<PlayerComponent>(entity);

        if(player.lifes <= 0)
        {
            notify(world, PlayerEndGameEvent{});
            transform.position = {0.f, 0.f, 0.f};
            player.lifes       = 4;
            player.score       = 0;
        }
    }
}
