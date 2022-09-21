#ifndef FREYR_SPACE_SHOOT_COMPONENT_HPP
#define FREYR_SPACE_SHOOT_COMPONENT_HPP

struct LaserGunComponent {
    float time = 0;
    bool triggered = false;
    unsigned maxShotsPerSecond = 2;
};

#endif //FREYR_SPACE_SHOOT_COMPONENT_HPP
