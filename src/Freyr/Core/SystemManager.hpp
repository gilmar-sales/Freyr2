#pragma once

#include "../Meta/MetaList.hpp"

#include <type_traits>

template<typename T, typename = std::void_t<>>
struct has_subscribers : std::false_type
{
};

template<typename T>
struct has_subscribers<T, std::void_t<decltype(std::declval<T>().m_subscribers)>> : std::true_type
{
};

FREYR_BEGIN

class World;

class FREYR_API SystemManager
{
  public:
    using Design     = ::Design;
    using SystemList = ::SystemList;
    using Bitset     = typename Design::Bitset;

    using SystemsContainer    = meta::rename<std::tuple, SystemList>;
    using SignaturesContainer = meta::generateTuple<Bitset, meta::sizeOf<SystemList>()>;

    SystemManager(World *world, unsigned capacity) : world(world)
    {
        resize(capacity);
        initializeSignatures();
        setupSystems();
    }

    template<typename System>
    void registerEntity(EntityID entity)
    {
        return std::get<meta::indexOf<System>()>(systems).registerEntity(entity);
    }

    template<typename System>
    void unregisterEntity(EntityID entity)
    {
        return std::get<meta::indexOf<System>()>(systems).unregisterEntity(entity);
    }

    template<typename System>
    Bitset &getSignature()
    {
        return std::get<meta::indexOf<System, SystemList>()>(signatures);
    }

    template<typename System>
    System &get()
    {
        return std::get<meta::indexOf<System, SystemList>()>(systems);
    }

    SystemsContainer &getSystems() { return systems; }

    template<typename... Systems>
    std::tuple<Systems &...> getSystems()
    {
        return {&std::get<meta::indexOf<Systems, SystemList>()>(systems)...};
    }

    void update(const std::function<void(void)> tearDown)
    {
        meta::forList(
            [this, tearDown](auto &system) {
                system.getRegisteredEntities().sort();
                system.onUpdate();
                tearDown();
            },
            systems);
    }

    void resize(unsigned size)
    {
        meta::forList([this, size](auto &system) { system.resize(size); }, systems);
    }

  private:
    void initializeSignatures()
    {
        meta::forList(
            [this](auto &system) {
                using System = std::remove_reference_t<decltype(system)>;
                meta::forList(
                    [this](auto sig) {
                        using Sig = decltype(sig);

                        if (Design::template isComponent<Sig>())
                            std::get<meta::indexOf<System, SystemsContainer>()>(
                                signatures)[Design::template componentBit<Sig>()] = 1;
                        else if (Design::template isTag<Sig>())
                            std::get<meta::indexOf<System, SystemsContainer>()>(
                                signatures)[Design::template tagBit<Sig>()] = 1;
                    },
                    typename System::Signature{});
            },
            systems);
    }

    template<typename... Systems>
    std::tuple<Systems *...> getSystemsPtr(std::tuple<Systems *...> a = {})
    {
        return {&std::get<meta::indexOf<Systems, SystemList>()>(systems)...};
    }

    void setupSystems()
    {
        auto manager = this;
        meta::forList(
            [manager](auto &system) {
                using system_t = std::remove_reference_t<decltype(system)>;

                if constexpr (has_subscribers<system_t>::value)
                {
                    system.m_subscribers = manager->getSystemsPtr(system.m_subscribers);
                }

                system.world = manager->world;
            },
            systems);
    }

    SystemsContainer systems;
    SignaturesContainer signatures;
    World *world;
};

FREYR_END
