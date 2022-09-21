#pragma once

struct LaserGunComponent
{
    float time                 = 0;
    bool triggered             = false;
    unsigned maxShotsPerSecond = 2;
};
