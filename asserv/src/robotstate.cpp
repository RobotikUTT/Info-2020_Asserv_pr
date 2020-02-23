#include "robotstate.h"

#include <math.h>

#include "parameters.h"

RobotState robotState;

void RobotState::update() {
    static int leftLastTicks = 0, rightLastTicks = 0;
    
    int leftTicks = leftEnc.read();
    int rightTicks = - rightEnc.read(); // minus sign because motors are in opposite directions
    
    float dLeft = (float)(leftTicks - leftLastTicks) * DISTANCE_PER_TICK;
    float dRight = (float)(rightTicks - rightLastTicks) * DISTANCE_PER_TICK;
    
    wheelSpeeds.left = dLeft * RATE_HZ;
    wheelSpeeds.right = dRight * RATE_HZ;

    float dAngle = atan2((dRight - dLeft), ENTRAXE);
    
    pose.theta += dAngle;
    pose.theta = fmod(pose.theta, 2 * M_PI);

    float dDistance = (dRight + dLeft) / (float)2.0;
    static float lastAngle = 0;
    float meanTrajAngle = (pose.theta + lastAngle) / (float)2.0;

    pose.x += dDistance * cos(meanTrajAngle); // TODO make sure angle is in rad
    pose.y += dDistance * sin(meanTrajAngle); // if angle is in degrees : * 180 / M_PI

    lastAngle = pose.theta;
    rightLastTicks = rightTicks;
    leftLastTicks = leftTicks;
}