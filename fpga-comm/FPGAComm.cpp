#include "FPGAComm.h"

#include <wirish/wirish.h>

// last packet and interrupt handlers
volatile FPGAInPacket lastPacket;
void FGPACommIH();

// blank constructor
FPGAComm::FPGAComm()
{
	// blank out the last packet
	memset(&lastPacket, 0, sizeof(FPGAInPacket));

	initialized = false;
}

FPGAComm::init(uint8 inPin, uint8 outPin, uint8 intPin)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->intPin = intPin;

	// properly configure the pins
	pinMode(inPin, INPUT);
	pinMode(outPin, OUTPUT);

	// attach the interrupt
	attachInterrupt(intPin, FPGACommIH, RISING);
}

FPGAComm::deinit()
{
	detachInterrupt(intPin);

	initialized = false;
}

// blank destructor
FPGAComm:~FPGAComm()
{
}

// intterrupt handler
void FPGACommIH()
{
	
}