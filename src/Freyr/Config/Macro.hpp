#pragma once

#define FREYR_BEGIN \
    namespace freyr \
    {
#define FREYR_END } // namespace Freyr

#ifdef BUILD_SHARED_LIBS
#ifdef _WIN32
#define FREYR_EXPORT __declspec(dllexport)
#else
#define FREYR_EXPORT
#endif
#else
#define FREYR_EXPORT
#endif

#ifdef FREYR_BUILDING_TESTS
#define FREYR_SPEC virtual
#else
#define FREYR_SPEC inline
#endif
