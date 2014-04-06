#ifndef ENCODER_CPP
#define ENCODER_CPP

#include "encoder.h"

Encoder::Encoder(int interruptPin)
{

	direction = FORWARD;
	ticks = 0;

	// bind an interrupt on this pin
}

int Encoder::getTicks()
{
	return ticks;
}

void encoder_interrupt_handler()
{
	// figure out which pin was triggered
	// and get the instance to that class
}

#endif
