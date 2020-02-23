/**
 * \file robotstate.h
 * \brief Class which holds position and speed data and updates with coders.
 * \author Paul Constant <constantpaul@hotmail.fr>
 * \date 2020/02/23
**/

#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#define ENCODER_USE_INTERRUPTS
#include "Encoder.h"

#include "pins.h"

typedef struct {float x, y, theta;} Pose;
typedef struct {float left, right;} WheelSpeeds;

class RobotState  {
public:
    /**
    * \brief Updates wheel speeds and pose from coders.
    **/
    void update();

    inline const Pose getPose() const { return pose; }
    inline const WheelSpeeds getWheelSpeeds() const { return wheelSpeeds; }
private:
    Pose pose = {0, 0, 0}; // mm, mm, rad
    WheelSpeeds wheelSpeeds = {0,0}; // mm/s, mm/s

    Encoder rightEnc = Encoder(A_RIGHT, B_RIGHT);
    Encoder leftEnc = Encoder(A_LEFT, B_LEFT);
};

#endif