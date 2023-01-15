#pragma once

#include <Freyr/Core/PublisherSystem.hpp>

#include "../Core/KeyCodes.hpp"

class PlayerMoveSystem;
class ShootSystem;

class InputSystem : public freyr::PublisherSystem<PlayerMoveSystem, ShootSystem>
{
  public:
    using Signature = std::tuple<>;
    void onUpdate() override;

  private:
    SparseSet<KeyCode> m_pressedKeys;
};