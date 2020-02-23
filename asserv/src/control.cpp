#include "control.h"

#include "pins.h"
#include "robotstate.h"
#include "collisions.h"

Control control;

extern RobotState robotState;
extern Collisions collisions;

namespace { // private functions

float filterLinearSpeed(float speed, float maxSpeed = 0) {
    static float lastSpeed = 0;
    
    if (!maxSpeed) {
        maxSpeed = MAX_SPEED;
    }
    
    if (speed >= 0) {
        if (speed > collisions.getMaxSpeed()) {
            speed = collisions.getMaxSpeed();
        }
        if (speed > maxSpeed) {
                speed = maxSpeed;
        }
        if (speed - lastSpeed > MAX_ACCELERATION_DIFFERENCE) {
            speed = lastSpeed + MAX_ACCELERATION_DIFFERENCE;
        } else if (speed - lastSpeed < - MAX_BRAKE_DIFFERENCE) {
            speed = lastSpeed - MAX_BRAKE_DIFFERENCE;
        }
    } else { // speed < 0 : going backwards
        if (speed < - collisions.getMaxSpeed()) {
            speed = - collisions.getMaxSpeed();
        }
        if (speed < - maxSpeed) {
            speed = - maxSpeed;
        }
        if (speed - lastSpeed < - MAX_ACCELERATION_DIFFERENCE) {
            speed = lastSpeed - MAX_ACCELERATION_DIFFERENCE;
        } else if (speed - lastSpeed > MAX_BRAKE_DIFFERENCE) {
            speed = lastSpeed + MAX_BRAKE_DIFFERENCE;
        }   
    }

    lastSpeed = speed;
    return speed;
}

void sendPWM(PID pid, float error, int FORWARD_PIN, int BACKWARDS_PIN, int PWM_PIN) {
    int pwm = pid.output(error);
    if (pwm > 255) {
        pwm = 255;
    } else if (pwm < - 255) {
        pwm = - 255;
    }

    if (pwm >= 0) {
        digitalWrite(FORWARD_PIN, HIGH);
        digitalWrite(BACKWARDS_PIN, LOW);
        analogWrite(PWM_PIN, pwm);
    } else {
        digitalWrite(FORWARD_PIN, LOW);
        digitalWrite(BACKWARDS_PIN, HIGH);
        analogWrite(PWM_PIN, - pwm);
    }
}

} // anonymous namespace

void Control::resetPIDs() {
    linearPID.resetErrors();
    angularPID.resetErrors();
}

void Control::updateSpeeds(float distanceError, float thetaError, float maxLinearSpeed) {
    targetLinearSpeed = filterLinearSpeed(linearPID.output(distanceError), maxLinearSpeed);
    targetAngularSpeed = angularPID.output(thetaError); // no collisions or speed check on angular speed
    updatePWM();
}

void Control::updatePWM() {
    float targetLeftSpeed = targetLinearSpeed - targetAngularSpeed;
    float targetRightSpeed = targetLinearSpeed + targetAngularSpeed;

    float leftError = targetLeftSpeed - robotState.getWheelSpeeds().left;
    float rightError = targetRightSpeed - robotState.getWheelSpeeds().right;

    sendPWM(leftWheelPID, leftError, FORWARD_LEFT, BACKWARDS_LEFT, PWM_LEFT);
    sendPWM(rightWheelPID, rightError, FORWARD_RIGHT, BACKWARDS_RIGHT, PWM_RIGHT);
}