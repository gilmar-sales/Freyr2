#pragma once

#include <tuple>
#include <utility>

#if defined(__linux__) || defined(__MINGW32__)
#include <experimental/tuple>
#endif

#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

FREYR_BEGIN

namespace meta
{
    template<typename TF, typename... Ts>
    auto forArgs(TF &&f, Ts &&...xs)
    {
        return (void)std::initializer_list<int>{(f(FWD(xs)), 0)...};
    }

    template<typename TF, typename TTuple>
    void forList(TF &&f, TTuple &&t)
    {
        auto adapted = [f = FWD(f)](auto &&...xs) { forArgs(f, FWD(xs)...); };

#if defined(__linux__) || defined(__MINGW32__)
        std::experimental::apply(adapted, FWD(t));
#else
        std::apply(adapted, FWD(t));
#endif // __linux__
    }
} // namespace meta

FREYR_END
