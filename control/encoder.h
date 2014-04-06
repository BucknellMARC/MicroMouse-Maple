#ifndef ENCODER_H
#define ENCODER_H

#define FORWARD 1
#define BACKWARD -1

class Encoder
{
private:
	uint8 interrputPin;

	int direction;
	int ticks;

public:
	Encoder(uint8 interruptPin);

	int getTicks();

	~Encoder();
};

void encoder_interrupt_handler();

#endif
