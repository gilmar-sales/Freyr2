cmake_minimum_required(VERSION 3.10)

project(
        Freyr
        LANGUAGES C CXX
)

file(GLOB_RECURSE FREYR_SOURCE
        src/*.hpp
        src/*.cpp
        )

add_library(freyr INTERFACE ${FREYR_SRC})
add_library(freyr::freyr ALIAS freyr)

target_include_directories(freyr INTERFACE
        $<BUILD_INTERFACE:${freyr_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/src>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_compile_features(freyr INTERFACE cxx_std_20)

target_precompile_headers(
        freyr
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

set_target_properties(freyr PROPERTIES PUBLIC_HEADER "src/Freyr/Freyr.hpp")
install(TARGETS freyr)
