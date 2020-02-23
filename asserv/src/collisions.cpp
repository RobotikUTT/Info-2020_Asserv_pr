#include "collisions.h"

#include "pins.h"

Collisions collisions;

void Collisions::update() {
    float distToObstacle = 9999999999; // mm // TODO fetch it from sensors
    maxSpeed = COLLISIONS_SPEED_COEFF * (distToObstacle - COLLISIONS_STOP_DISTANCE);
    if (maxSpeed < 0) {
        maxSpeed = 0;
    }
}
