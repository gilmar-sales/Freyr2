#ifndef SPACE_ECS_METEOR_MANAGER_SYSTEM_HPP
#define SPACE_ECS_METEOR_MANAGER_SYSTEM_HPP

#include <iostream>
#include <random>

#include <Freyr/Core/BaseSystem.hpp>

#include "../Core/Time.hpp"
#include "../Core/Input.hpp"
#include "../Core/TextureManager.hpp"
#include "../Events/GameEvents.hpp"

struct EnemyTag;

class Application;

class MeteorManagerSystem : public freyr::BaseSystem {
public:
    using Signature = std::tuple<EnemyTag>;

    MeteorManagerSystem() = default;

    ~MeteorManagerSystem() = default;

    void onUpdate() override;

    void onReceive(PlayerEndGameEvent event);

private:
    int firstWave = 5;
    int secondWave = 8;

    int currentWave = firstWave;
    int nextWave = secondWave;
};

#endif // SPACE_ECS_METEOR_MANAGER_SYSTEM_HPP
