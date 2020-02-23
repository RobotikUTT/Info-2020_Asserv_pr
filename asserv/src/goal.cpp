#include "goal.h"

#include <math.h>

#include "control.h"
#include "robotstate.h"

extern RobotState robotState;
extern Control control;

void Rot::process() {
    float thetaError = theta - robotState.getPose().theta;
    if (thetaError < THETA_ERROR_TOLERANCE) {
        reached = true;
    }
    
    control.updateSpeeds(0, thetaError);
}

void Goto::process() {
    float dx = x - robotState.getPose().x;
    float dy = y - robotState.getPose().y;

    float distanceError = sqrt(pow(dx, 2) + pow(dy, 2));
    float thetaError = atan2(dy, dx) - robotState.getPose().theta;

    if (distanceError < DIST_ERROR_TOLERANCE) {
        reached = true;
    }

    if (thetaError > THETA_ERROR_TOLERANCE) {
        // rotate only
        distanceError = 0;
    } 

    control.updateSpeeds(distanceError, thetaError, speed);
}
