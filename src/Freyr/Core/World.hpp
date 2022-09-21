#pragma once

#include "ComponentManager.hpp"
#include "Design.hpp"
#include "EntityManager.hpp"
#include "SystemManager.hpp"

FREYR_BEGIN

class FREYR_API World
{
  public:
    using Design        = typename ::Design;
    using ComponentList = typename Design::ComponentList;
    using TagList       = typename Design::TagList;
    using Bitset        = typename Design::Bitset;

    explicit World(unsigned capacity = 1024)
        : entityManager(capacity), componentManager(capacity), systemManager(this, capacity),
          entitiesMarkedToDestroy(capacity), capacity(capacity)
    {
    }

    ~World() = default;

    EntityID createEntity()
    {
        if(entityManager.getNextEntity() >= capacity) resize(capacity * 2);

        componentManager.resetComponents(entityManager.getNextEntity());

        return entityManager.create();
    }

    void destroyEntity(EntityID entity)
    {
        entitiesMarkedToDestroy.insert(entity);
    }

    template<typename T>
    bool hasComponent(EntityID entity)
    {
        return entityManager.template hasComponent<T>(entity);
    }

    template<typename T>
    T &getComponent(EntityID entity)
    {
        return componentManager.template getComponent<T>(entity);
    }

    template<typename... Ts>
    std::tuple<Ts &...> getComponents(EntityID entity)
    {
        return {getComponent<Ts>(entity)...};
    }

    template<typename T>
    T &addComponent(EntityID entity)
    {
        entityManager.template addComponent<T>(entity);

        meta::forList(
            [this, entity](auto &system) {
                using system_t = std::remove_reference_t<decltype(system)>;

                auto &systemSignature = systemManager.getSignature<system_t>();

                if((systemSignature & entityManager.getSignature(entity)) == systemSignature)
                {
                    system.registerEntity(entity);
                }
            },
            systemManager.getSystems());

        return componentManager.template getComponent<T>(entity);
    }

    template<typename T>
    T &addComponent(EntityID entity, T value)
    {
        addComponent<T>(entity);

        componentManager.template setComponent<T>(entity, value);

        return componentManager.template getComponent<T>(entity);
    }

    template<typename... Ts>
    std::tuple<Ts &...> addComponents(EntityID entity)
    {
        return {addComponent<Ts>(entity)...};
    }

    template<typename... Ts>
    std::tuple<Ts &...> addComponents(EntityID entity, Ts... components)
    {
        return {addComponent<Ts>(entity, components)...};
    }

    template<typename T>
    void removeComponent(EntityID entity)
    {
        entityManager.template removeComponent<T>(entity);

        meta::forList(
            [this, entity](auto &system) {
                using system_t = std::remove_reference_t<decltype(system)>;

                auto &sys_sig = systemManager.getSignature<system_t>();

                if((sys_sig & entityManager.getSignature(entity)) != sys_sig)
                {
                    system.unregisterEntity(entity);
                }
            },
            systemManager.getSystems());
    }

    template<typename T>
    bool addTag(EntityID id)
    {
        entityManager.template addTag<T>(id);

        meta::forList(
            [this, id](auto &system) {
                using system_t = std::remove_reference_t<decltype(system)>;

                auto &sys_sig = systemManager.getSignature<system_t>();

                if((sys_sig & entityManager.getSignature(id)) == sys_sig)
                {
                    system.registerEntity(id);
                }
            },
            systemManager.getSystems());

        return true;
    }

    template<typename T>
    bool hasTag(EntityID entity)
    {
        return entityManager.template hasTag<T>(entity);
    }

    void update()
    {
        systemManager.update([this]() { tearDown(); });
    }

    EntityManager &entities()
    {
        return entityManager;
    }

    ComponentManager &components()
    {
        return componentManager;
    }

    SystemManager &systems()
    {
        return systemManager;
    }

    Design &getDesign()
    {
        return design;
    }

  protected:
    void tearDown()
    {
        entitiesMarkedToDestroy.sort();
        for(auto entity: entitiesMarkedToDestroy)
        {
            _destroyEntity(entity);
        }

        entitiesMarkedToDestroy.clear();
    }

  private:
    void resize(unsigned size)
    {
        entityManager.resize(size);
        componentManager.resize(size);
        systemManager.resize(size);
        entitiesMarkedToDestroy.resize(size);

        capacity = size;
    }

    void _destroyEntity(EntityID entity)
    {
        auto lastEntity = entityManager.getNextEntity() - 1;
        if(entity < lastEntity)
        {
            meta::forList(
                [this, entity, lastEntity](auto &system) {
                    using system_t = std::remove_reference_t<decltype(system)>;
                    system.unregisterEntity(entity);
                    system.unregisterEntity(lastEntity);
                },
                systemManager.getSystems());

            meta::forList(
                [this, entity, lastEntity](auto &system) {
                    using system_t = std::remove_reference_t<decltype(system)>;

                    auto &systemSignature = this->systemManager.template getSignature<system_t>();

                    if((systemSignature & entityManager.getSignature(lastEntity)) == systemSignature)
                    {
                        system.registerEntity(entity);
                    }
                },
                systemManager.getSystems());

            components().moveData(lastEntity, entity);
        }
        else
        {
            meta::forList(
                [this, entity, lastEntity](auto &system) {
                    using system_t = std::remove_reference_t<decltype(system)>;
                    system.unregisterEntity(entity);
                },
                systemManager.getSystems());
        }
        entityManager.destroy(entity);
    }

    EntityManager entityManager;
    ComponentManager componentManager;
    SystemManager systemManager;
    Design design;
    SparseSet<EntityID> entitiesMarkedToDestroy;
    unsigned capacity;
};

FREYR_END
