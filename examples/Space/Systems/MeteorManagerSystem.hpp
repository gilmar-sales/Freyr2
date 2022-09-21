#pragma once

#include <Freyr/Core/BaseSystem.hpp>

#include "../Events/GameEvents.hpp"

struct EnemyTag;

class Application;

class MeteorManagerSystem: public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<EnemyTag>;

    MeteorManagerSystem() = default;

    ~MeteorManagerSystem() = default;

    void onUpdate() override;

    void onReceive(PlayerEndGameEvent event);

  private:
    int firstWave  = 5;
    int secondWave = 8;

    int currentWave = firstWave;
    int nextWave    = secondWave;
};
