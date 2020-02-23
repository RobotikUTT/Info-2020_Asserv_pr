/**
 * \file parameters.h
 * \brief All params used for @see asserv.ino.
 * \author Paul Constant <constantpaul@hotmail.fr>
 * \date 2020/02/23
**/

#ifndef PARAMETERS_H
#define PARAMETERS_H

// Main loop
#define RATE_HZ 20 // Hz
#define TIMER_MS 1000.0 / (float)RATE_HZ // ms

// Goals list
#define MAX_SIMULTANEOUS_GOALS 50

// Speed constants
#define MAX_SPEED 1000 // mm/s
#define MAX_ACCEL 1500 // mm/s^2
#define MAX_ACCELERATION_DIFFERENCE MAX_ACCEL / RATE_HZ // mm/s
#define BRAKE_COEFF 3 // brakes BRAKE_COEFF times more than accelerates
#define MAX_BRAKE_DIFFERENCE MAX_ACCELERATION_DIFFERENCE * BRAKE_COEFF // mm/s

// Robot state
#define WHEEL_DIAMETER 56 // mm
#define TICKS_PER_ROTATION (48 * 47)
#define DISTANCE_PER_TICK WHEEL_DIAMETER * 3.14159265358979323846 / TICKS_PER_ROTATION

#define ENTRAXE 217 // mm

// Collisions
#define COLLISIONS_SPEED_COEFF 0.5 
#define COLLISIONS_STOP_DISTANCE 250 // mm

// Goals
#define DIST_ERROR_TOLERANCE 10 // mm
#define THETA_ERROR_TOLERANCE 0.05 // rad

#endif // PARAMETERS_H