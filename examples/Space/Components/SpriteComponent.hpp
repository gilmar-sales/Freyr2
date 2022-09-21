#pragma once

struct SpriteComponent
{
    unsigned width;
    unsigned height;
    unsigned texture;
    unsigned texturesCount;
    float frameTime;
    unsigned currentFrame;
};
