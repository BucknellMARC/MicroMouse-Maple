#ifndef MOTOR_H
#define MOTOR_H

#include "Encoder.h"

class Motor
{
private:
	uint8 pwmPin, directionPin, brakePin;

	float power;

	int direction;
	int brake;
public:
	Motor(uint8 pwmPin, uint8 directionPin, uint8 brakePin);

	// setters //
	void setPower(float power);		// number between -1 and 1
	void setDirection(int direction);
	void setBrake(int brake);

	// getters //
	float getPower();
	int getDirection();
	int getBrake();

	~Motor();
};

#endif
