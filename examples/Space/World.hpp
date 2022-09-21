#pragma once

#include "Design.hpp"

#include "Systems/CollisionSystem.hpp"
#include "Systems/CombatSystem.hpp"
#include "Systems/DecaySystem.hpp"
#include "Systems/MeteorManagerSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/PlayerMoveSystem.hpp"
#include "Systems/PlayerSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ShootSystem.hpp"

using SystemList = std::tuple<PhysicsSystem, RenderSystem, PlayerMoveSystem, MeteorManagerSystem, ShootSystem,
                              DecaySystem, CollisionSystem, PlayerSystem, CombatSystem>;

#include <Freyr/Core/World.hpp>
