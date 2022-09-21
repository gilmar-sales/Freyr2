#ifndef SPACE_ECS_DECAY_SYSTEM_HPP
#define SPACE_ECS_DECAY_SYSTEM_HPP

#include <Freyr/Core/BaseSystem.hpp>

#include <iostream>

#include "../Core/Time.hpp"


struct DecayComponent;
struct BulletTag;

class Application;

    class DecaySystem : public freyr::BaseSystem {
    public:
        using Signature = std::tuple<DecayComponent>;

        DecaySystem() = default;

        ~DecaySystem() = default;

        void onUpdate() override;
    };

#endif // SPACE_ECS_DECAY_SYSTEM_HPP
