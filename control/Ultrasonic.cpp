#ifndef ULTRASONIC_CPP
#define ULTRASONIC_CPP

#include <wirish/wirish.h>

#include "Ultrasonic.h"

PingUltrasonic::PingUltrasonic(int listenPin)
{
	// set up the PWM listen pin
	this->listenPin = listenPin;
}

int PingUltrasonic::readValue()
{
	// output pulse for 5 usec
	pinMode(listenPin, OUTPUT);
	digitalWrite(listenPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(listenPin, LOW);

	// sit and spin until ultrasonic response
	pinMode(listenPin, INPUT);

	while(!digitalRead(listenPin));

	int usecs;

	// increment usecd the pin is high, minimum number of usecs is 115
	for(usecs = -115 ;digitalRead(listenPin); usecs++) {
		delayMicroseconds(1);
	}

	return usecs;
}

PingUltrasonic::~PingUltrasonic()
{

}

#endif
