#pragma once

#include "../Core/KeyCodes.hpp"

struct KeyDownEvent
{
    KeyCode key;
};

struct KeyUpEvent
{
    KeyCode key;
};

struct KeyPressedEvent
{
    KeyCode key;
    float value;
};

struct PlayerShootEvent
{
};

struct PlayerMoveEvent
{
    glm::vec2 direction;
};
