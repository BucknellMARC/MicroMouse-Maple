#ifndef MOTOR_CPP
#define MOTOR_CPP

#include <wirish/wirish.h>

#include "encoder.h"
#include "Motor.h"

Motor::Motor(uint8 pwmPin, uint8 directionPin)
{
	this->pwmPin = pwmPin;
	this->directionPin = directionPin;

	pinMode(pwmPin, PWM);
	pinMode(directionPin, OUTPUT);
}

void Motor::setPower(float power)
{
	if (power < 0) {
		this->power = -power;
		this->direction = BACKWARD;
	}
	else {
		this->power = power;
		this->direction = FORWARD;
	}

	pwmWrite(pwmPower, this->power * 255);
	// write the direction pin
}

int Motor::getDirection()
{
	return direction;
}

float Motor::getPower()
{
	if (direction == BACKWARD) {
		return -power;
	}

	return power;
}

Motor::~Motor()
{
}

#endif
