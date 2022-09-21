#pragma once

struct PlayerDeathEvent
{
    freyr::EntityID killer;
};

struct PlayerEndGameEvent
{
};

struct CollisionEvent
{
    freyr::EntityID collisor;
    freyr::EntityID target;
};
