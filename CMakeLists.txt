cmake_minimum_required(VERSION 3.15)
project(freyr CXX)

file(GLOB_RECURSE FREYR_SOURCE
    src/*.hpp
    src/*.cpp
)

add_library(freyr INTERFACE ${FREYR_SRC})

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
        src/Freyr/Config/Macro.hpp
)

set_target_properties(freyr PROPERTIES PUBLIC_HEADER "src/Freyr/Freyr.hpp")
install(TARGETS freyr)
