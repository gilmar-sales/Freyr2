#pragma once

#include "Design.hpp"

#include "Systems/CollisionSystem.hpp"
#include "Systems/CombatSystem.hpp"
#include "Systems/DecaySystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/MeteorManagerSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/PlayerMoveSystem.hpp"
#include "Systems/PlayerSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ScreenLimiterSystem.hpp"
#include "Systems/ShootSystem.hpp"

using SystemList = std::tuple<InputSystem, PhysicsSystem, ScreenLimiterSystem, PlayerMoveSystem, MeteorManagerSystem,
                              ShootSystem, DecaySystem, CollisionSystem, PlayerSystem, CombatSystem, RenderSystem>;

#include "Events/InputEvents.hpp"

#include <FreyrCT/Core/World.hpp>
