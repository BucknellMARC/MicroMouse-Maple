#ifndef PIDCONTROLLER_CPP
#define PIDCONTROLLER_CPP

#include "PIDController.h"

PIDController::PIDController(float p, float i, float d)
{
	// save away the constants
	this->kp = p;
	this->ki = i;
	this->kd = d;

	i = 0;
}

void PIDController::setSetpoint(float setpoint)
{
	this->setpoint = setpoint;
}

float PIDController::calculate()
{
	float pos = 0;			// CHANGE - stubbed value

	// compute the PID values
	float p = pos - setpoint;
	i += pos - setpoint;
	float d = (pos - setpoint) - (pos - lastPos);

	// return the sum of the values
	return kp * p + ki * i + kd * d;
}

PIDController::~PIDController()
{

}

#endif
