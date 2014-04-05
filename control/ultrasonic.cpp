#ifndef ULTRASONIC_CPP

#include "ultrasonic.h"

#include <wirish/wirish.h>

PingUltrasonic::PingUltrasonic(int listenPin)
{
	// set up the PWM listen pin
	this->listenPin = listenPin;
	pinMode(listenPin, INPUT_ANALOG);
}

PingUltrasonic::getLastDistance()
{
	return lastDistance;
}

PingUltrasonic::~PingUltrasonic()
{

}

#endif
