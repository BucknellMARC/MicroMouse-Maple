#ifndef ULTRASONIC_H

#include <wirish/wirish.h>

class PingUltrasonic
{
private: 
	uint8 listenPin;

	volatile int lastDistance;
public:
	PingUltrasonic(int listenPin);

	int getLastDistance();

	~PingUltrasonic();
};

#endif
