#ifndef FREYR_SPACE_SPRITECOMPONENT_H
#define FREYR_SPACE_SPRITECOMPONENT_H

#include <vector>

struct SpriteComponent {
    unsigned width;
    unsigned height;
    unsigned texture;
    unsigned texturesCount;
    float frameTime;
    unsigned currentFrame;
};

#endif //FREYR_SPACE_SPRITECOMPONENT_H
