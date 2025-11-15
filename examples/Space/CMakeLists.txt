file(GLOB_RECURSE SPACE_SOURCE *.cpp *.hpp)

add_executable(Space ${SPACE_SOURCE})

find_package(OpenGL)

if (MSVC)
    target_compile_options(Space PUBLIC "/ZI")
    target_link_options(Space PUBLIC "/INCREMENTAL")
endif ()

target_link_libraries(Space
        PUBLIC
        freyr
        glad
        glm
        ${OpenGL_LIBRARY}
        SDL3::SDL3
)

target_precompile_headers(Space
        PRIVATE
        <iostream>
        <vector>
        <string>
        <tuple>
        <glad/glad.h>
        <SDL3/SDL.h>
        <glm/glm.hpp>
)

file(COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)