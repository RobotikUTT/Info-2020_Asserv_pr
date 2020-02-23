#include "pid.h"

PID::PID(float P, float I, float D, float maxIError) : P(P), I(I), D(D), maxIError(maxIError) {}

float PID::output(float newError) {
	updateErrors(newError);
	return P * error + I * errorSum + D * lastError;
}

void PID::updateErrors(float newError) {
	error = newError;
	errorSum += error;
	if (errorSum > maxIError) {
		errorSum = maxIError;
	} else if (errorSum < - maxIError) {
		errorSum = - maxIError;
	}
	lastError = error;
}

void PID::resetErrors() {
	error = 0;
	lastError = 0;
	errorSum = 0;
}