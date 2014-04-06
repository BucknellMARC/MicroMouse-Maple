#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <wirish/wirish.h>

class PingUltrasonic
{
private: 
	uint8 listenPin;

public:
	PingUltrasonic(int listenPin);

	int readValue();

	~PingUltrasonic();
};

#endif
