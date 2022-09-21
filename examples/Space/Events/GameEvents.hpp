#ifndef CT_ECS_GAME_EVENTS_H
#define CT_ECS_GAME_EVENTS_H


struct PlayerDeathEvent {
    freyr::EntityID killer;
};

struct PlayerEndGameEvent {

};

struct CollisionEvent {
    freyr::EntityID collisor;
    freyr::EntityID target;
};

#endif //CT_ECS_GAME_EVENTS_H
