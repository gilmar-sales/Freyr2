#pragma once

#include "../Types/Entity.hpp"

FREYR_BEGIN

class World;

/**
 * @brief The EntityManager will create entity ids and keep them contiguous
 *
 * @tparam TDesign
 */
class FREYR_API EntityManager
{
  public:
    using Design = ::Design;
    using ComponentList = typename Design::ComponentList;
    using TagList = typename Design::TagList;
    using Bitset = typename Design::Bitset;

    explicit EntityManager(unsigned int size = 1024): nextEntity{0}, signatures(size) {}

    ~EntityManager() = default;

    template<typename T>
    void addComponent(EntityID entity)
    {
        signatures[entity][Design::template componentBit<T>()] = 1;
    }

    template<typename T>
    void removeComponent(EntityID entity)
    {
        signatures[entity][Design::template componentBit<T>()] = 0;
    }

    template<typename T>
    bool hasComponent(EntityID entity)
    {
        return signatures[entity][Design::template componentBit<T>()];
    }

    template<typename T>
    void addTag(EntityID entity)
    {
        signatures[entity][Design::template tagBit<T>()] = 1;
    }

    template<typename T>
    void removeTag(EntityID entity)
    {
        signatures[entity][Design::template tagBit<T>()] = 0;
    }

    template<typename T>

    bool hasTag(EntityID entity)
    {
        return signatures[entity][Design::template tagBit<T>()];
    }

    Bitset &getSignature(EntityID entity)
    {
        return signatures[entity];
    }

    void resize(unsigned size)
    {
        signatures.resize(size);
    }

    EntityID getNextEntity()
    {
        return nextEntity;
    }

    inline void forEach(const std::function<void(EntityID)> &function)
    {
        for(EntityID entity = 0; entity < nextEntity; entity++)
        {
            function(entity);
        }
    }

    EntityID create()
    {
        signatures[nextEntity].reset();
        return nextEntity++;
    }

    void destroy(EntityID entity)
    {
        EntityID lastEntity = nextEntity - 1;

        if(entity < lastEntity)
        {
            signatures[entity] = signatures[lastEntity];
            signatures[lastEntity].reset();
        }
        else
        {
            signatures[entity].reset();
        }

        --nextEntity;
    }

    friend class World;
    friend class EntityManagerSpec;

  private:
    EntityID nextEntity;
    std::vector<Bitset> signatures;
};

FREYR_END
