#ifndef MOTOR_CPP
#define MOTOR_CPP

#include <wirish/wirish.h>

#include "Encoder.h"
#include "Motor.h"

Motor::Motor(uint8 pwmPin, uint8 directionPin, uint8 brakePin)
{
	// configure the pins
	pinMode(pwmPin, PWM);
	pinMode(directionPin, OUTPUT);
	pinMode(brakePin, OUTPUT);

	// init with power at 0
	this->pwmPin = pwmPin;
	setPower(0.0f);

	// set direction to forward to start out
	this->directionPin = directionPin;
	setDirection(FORWARD);

	// brake is on to start
	this->brakePin = brakePin;
	setBrake(1);
}

void Motor::setPower(float power)
{
	this->power = power;
	pwmWrite(pwmPin, power * 255);
}

void Motor::setDirection(int direction)
{
	this->direction = direction;

	if (direction) {
		digitalWrite(directionPin, HIGH);
	}
	else {
		digitalWrite(directionPin, LOW);
	}
}

void Motor::setBrake(int brake)
{
	this->brake = brake;

	if (brake) {
		digitalWrite(brakePin, HIGH);
	}
	else {
		digitalWrite(brakePin, LOW);
	}
}

float Motor::getPower()
{
	return power;
}

int Motor::getDirection()
{
	return direction;
}

int Motor::getBrake()
{
	return brake;
}

Motor::~Motor()
{
	// zero out all pins before releasing it
	pwmWrite(pwmPin, 0);
	digitalWrite(directionPin, LOW);
	digitalWrite(brakePin, LOW);
}

#endif
