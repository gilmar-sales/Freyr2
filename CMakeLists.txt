cmake_minimum_required(VERSION 3.29)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
        Freyr
        LANGUAGES C CXX
)

file(GLOB_RECURSE FREYR_SOURCE
        src/*.hpp
        src/*.cpp
        )

add_library(freyr_ct INTERFACE ${FREYR_SRC})
add_library(freyr_ct::freyr_ct ALIAS freyr_ct)

find_package(TBB QUIET)

if (${TBB_FOUND})
    target_link_libraries(freyr_ct INTERFACE TBB::tbb)
endif ()

target_include_directories(freyr_ct INTERFACE
        $<BUILD_INTERFACE:${freyr_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/src>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_compile_features(freyr_ct INTERFACE cxx_std_20)

target_precompile_headers(
    freyr_ct
        INTERFACE
        <vector>
        <tuple>
        <bitset>
        <memory>
        <functional>
        src/Freyr/Core/Macro.hpp
)

option(FREYR_BUILD_EXAMPLES "Build Freyr examples." OFF)

if (OPTION_BUILD_EXAMPLES)
    set(FREYR_BUILD_EXAMPLES ON)
endif ()

if (FREYR_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

option(FREYR_BUILD_TESTS "Build Freyr tests." OFF)

if (FREYR_BUILD_TESTS)
    add_subdirectory(tests)
endif ()

set_target_properties(freyr_ct PROPERTIES PUBLIC_HEADER "src/Freyr/Freyr.hpp")
install(TARGETS freyr_ct)
