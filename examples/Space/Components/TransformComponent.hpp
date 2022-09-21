#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

struct TransformComponent
{
    glm::vec3 position = {0, 0, 0};
    glm::vec3 scale    = {1, 1, 1};
    glm::vec3 rotation = {0, 0, 0};

    glm::vec3 getForwardDirection()
    {
        glm::vec4 front          = {0, 1, 0, 0};
        glm::mat4 rotationMatrix = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), {0, 0, 1});
        front          = front * rotationMatrix;

        return glm::normalize(glm::vec3(-front.x, front.y, front.z));
    }

    glm::vec3 getRightDirection()
    {
        glm::vec4 front          = {1, 0, 0, 0};
        glm::mat4 rotationMatrix = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };

        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), {0, 0, 1});
        front          = front * rotationMatrix;

        return glm::normalize(glm::vec3(front.x, -front.y, front.z));
    }
};
