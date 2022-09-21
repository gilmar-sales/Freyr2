#pragma once

#include <Freyr/Core/BaseSystem.hpp>

struct DecayComponent;
struct BulletTag;

class Application;

class DecaySystem: public freyr::BaseSystem
{
  public:
    using Signature = std::tuple<DecayComponent>;

    DecaySystem() = default;

    ~DecaySystem() = default;

    void onUpdate() override;
};
