#pragma once

#define FREYR_BEGIN namespace freyr {
#define FREYR_END } // namespace Freyr

#ifdef BUILD_SHARED_LIBRARIES
#define FREYR_API __declspec( dllexport )
#else
#define FREYR_API
#endif

#ifdef FREYR_BUILDING_TESTS
#define FREYR_SPEC virtual
#else
#define FREYR_SPEC inline
#endif

