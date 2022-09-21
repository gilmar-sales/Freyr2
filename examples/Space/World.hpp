#ifndef FREYR_EXAMPLE_WORLD_HPP
#define FREYR_EXAMPLE_WORLD_HPP

#include "Design.hpp"

#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/PlayerMoveSystem.hpp"
#include "Systems/MeteorManagerSystem.hpp"
#include "Systems/ShootSystem.hpp"
#include "Systems/DecaySystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/PlayerSystem.hpp"
#include "Systems/CombatSystem.hpp"

using SystemList = std::tuple<
        PhysicsSystem,
        RenderSystem,
        PlayerMoveSystem,
        MeteorManagerSystem,
        ShootSystem,
        DecaySystem,
        CollisionSystem,
        PlayerSystem,
        CombatSystem
        >;

#include <Freyr/Core/World.hpp>

#endif //FREYR_EXAMPLE_WORLD_HPP
