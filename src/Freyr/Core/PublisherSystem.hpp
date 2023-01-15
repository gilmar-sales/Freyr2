#pragma once

#include "../Meta/Iteration.hpp"
#include "BaseSystem.hpp"

FREYR_BEGIN

template<typename System, typename Event, typename = std::void_t<>>
struct has_event : std::false_type
{
};

template<typename Subscriber, typename Event>
struct has_event<Subscriber, Event, std::void_t<decltype(std::declval<Subscriber>().onReceive(std::declval<Event>()))>>
    : std::true_type
{
};

template<typename... Subscribers>
class PublisherSystem : public BaseSystem
{
  public:
    template<typename Event>
    void notify(const Event &event)
    {
        meta::forList(
            [event](auto subscriber) {
                using subscriber_t = std::remove_pointer_t<decltype(subscriber)>;
                if constexpr (has_event<subscriber_t, Event>::value)
                {
                    subscriber->onReceive(event);
                }
            },
            m_subscribers);
    }

    friend class SystemManager;

  protected:
    std::tuple<Subscribers *...> m_subscribers = {};
};

FREYR_END
