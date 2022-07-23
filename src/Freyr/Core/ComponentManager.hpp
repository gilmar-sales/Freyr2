#pragma once

#include "../Meta/Iteration.hpp"
#include "../Meta/MetaList.hpp"
#include "../Types/Entity.hpp"

FREYR_BEGIN

class FREYR_API ComponentManager
{
    using Design = ::Design;
    using ComponentList = Design::ComponentList;
    template<typename... Ts>
    using TupleOfVectors = meta::List<std::vector<Ts>...>;

    using ComponentVectors = meta::rename<TupleOfVectors, ComponentList>;

  public:
    explicit ComponentManager(unsigned long size)
    {
        resize(size);
    }

    ~ComponentManager() = default;

    void resize(size_t new_size)
    {
        meta::forList([this, new_size](auto &vector) { vector.resize(new_size); }, componentVectors);
    }

    template<typename T>
    void setComponent(EntityID id, T value)
    {
        std::get<std::vector<T>>(componentVectors)[id] = value;
    }

    template<typename T>
    T &getComponent(EntityID id)
    {
        return std::get<std::vector<T>>(componentVectors)[id];
    }

    void resetComponents(EntityID entity)
    {
        meta::forList([this, entity](auto &vector) { vector[entity] = {}; }, componentVectors);
    }

    void moveData(EntityID from, EntityID to)
    {
        meta::forList([this, from, to](auto &vector) { vector[to] = vector[from]; }, componentVectors);
    }

  private:
    ComponentVectors componentVectors{};
};

FREYR_END
