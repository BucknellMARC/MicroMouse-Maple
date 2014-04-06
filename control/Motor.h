#ifndef MOTOR_H
#define MOTOR_H

#include "encoder.h"

class Motor
{
private:
	uint8 pwmPin, directionPin;

	float power;

	int direction;
public:
	Motor(uint8 pwmPin, uint8 directionPin);

	void setPower(float power);		// number between -1 and 1

	int getDirection();
	float getPower();

	~Motor();
};

#endif
