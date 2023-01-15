#pragma once

#include "../Containers/SparseSet.hpp"
#include "../Types/Entity.hpp"

FREYR_BEGIN

class World;

class BaseSystem
{
  public:
    virtual void onUpdate() {}

    void registerEntity(EntityID id) { registeredEntities.insert(id); }

    void unregisterEntity(EntityID id) { registeredEntities.remove(id); }

    inline void resize(unsigned size) { registeredEntities.resize(size); }

    SparseSet<EntityID> &getRegisteredEntities() { return registeredEntities; }

  protected:
    BaseSystem(unsigned capacity = 1024u) : registeredEntities(capacity) { world = nullptr; }

    friend class SystemManager;
    friend class World;
    World *world;

  private:
    SparseSet<EntityID> registeredEntities;
};

FREYR_END
