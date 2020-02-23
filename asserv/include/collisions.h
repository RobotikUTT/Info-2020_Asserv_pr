/**
 * \file collisions.h
 * \brief Class which holds a maximal speed value based on the proximity of obstacles.
 * \author Paul Constant <constantpaul@hotmail.fr>
 * \date 2020/02/23
**/

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "parameters.h"

class Collisions  {
public:
    /**
     * Updates the maximal speed based on the distance to the nearest obstacle.
    **/
    void update();
    inline const float getMaxSpeed() const { return maxSpeed; }
    
private:
    int maxSpeed = MAX_SPEED; // mm/s
};

#endif // COLLISIONS_H