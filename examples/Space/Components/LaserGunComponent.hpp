#pragma once

struct LaserGunComponent
{
    float lastShootTime = 0;
    float reloadTime    = 0.5f;
    unsigned ammo       = 5;
    unsigned ammoSpent  = 0;
};
