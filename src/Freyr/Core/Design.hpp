#pragma once

#include "../Meta/MetaList.hpp"

FREYR_BEGIN

template<typename TComponentList, typename TTagList>
class Design
{
  public:
    using ComponentList = TComponentList;
    using TagList = TTagList;
    using ThisType = Design<ComponentList, TagList>;

    template<typename T>
    static constexpr bool isComponent() noexcept
    {
        return meta::contains<T, ComponentList>{};
    }

    template<typename T>
    static constexpr bool isTag() noexcept
    {
        return meta::contains<T, TagList>{};
    }

    static constexpr std::size_t componentCount() noexcept
    {
        return meta::sizeOf<ComponentList>();
    }

    static constexpr std::size_t tagCount() noexcept
    {
        return meta::sizeOf<TagList>();
    }

    template<typename T>
    static constexpr std::size_t componentId() noexcept
    {
        return meta::indexOf<T, ComponentList>();
    }

    template<typename T>
    static constexpr std::size_t tagId() noexcept
    {
        return meta::indexOf<T, TagList>();
    }

    using Bitset = std::bitset<componentCount() + tagCount()>;

    template<typename T>
    static constexpr std::size_t componentBit() noexcept
    {
        return componentId<T>();
    }

    template<typename T>
    static constexpr std::size_t tagBit() noexcept
    {
        return componentCount() + tagId<T>();
    }
};

FREYR_END
