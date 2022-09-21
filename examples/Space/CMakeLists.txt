file(GLOB_RECURSE SPACE_SOURCE *.cpp *.hpp)

add_executable(Space ${SPACE_SOURCE})

if(MSVC)
  target_compile_options(Space PUBLIC "/ZI")
  target_link_options(Space PUBLIC "/INCREMENTAL")
endif()

target_link_libraries(Space
        freyr
        glad
        glfw
        glm
        GL
        )

target_precompile_headers(Space
        PRIVATE
        <iostream>
        <vector>
        <string>
        <tuple>
        <glad/glad.h>
        <GLFW/glfw3.h>
        <glm/glm.hpp>
        )

file(COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)