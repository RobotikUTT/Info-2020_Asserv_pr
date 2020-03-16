/**
 * \file goal.h
 * \brief Multiple position goal classes which send position errors to @see control.h.
 * \author Paul Constant <constantpaul@hotmail.fr>
 * \date 2020/02/23
**/

#ifndef GOAL_H
#define GOAL_H

#include "parameters.h"

/**
 * \brief Mother goal class. Represents an empty goal.
**/
class Goal {
public:
    /**
     * \brief Sends the position error to @see control.h.
     * subclasses must override this function.
    **/
    void process() { reached = true; }

    inline const bool isReached() const { return reached; }

protected:
    bool reached = false;
};

/**
 * \brief Rotates to a given angle in radians.
**/
class Rot : public Goal {
public:
    Rot() = delete;
    Rot(float theta) : Goal(), theta(theta) {}

    void process();

private:
    float theta; // rad
};

/**
 * \brief Goes to a given (x,y) absolute position in mm
**/
class Goto : public Goal {
public:
    Goto() = delete;

    /**
     * \brief constructor of Goto order.
     * \param x x coordinate in mm
     * \param y y coordinate in mm
     * \param maxSpeed max speed at which we want to go in mm/s. Cannot exceed MAX_SPEED. 0 for default.
    **/
    Goto(float x, float y, float maxSpeed = 0) : Goal(), x(x), y(y), maxSpeed(maxSpeed) {}

    void process();

private:
    float x, y, maxSpeed; // mm, mm, mm/s
};

// add new goals here and override process()

#endif // GOAL_H