#ifndef FPGA_COMM_CPP
#define FPGA_COMM_CPP

#include "FPGAComm.h"

#include <wirish/wirish.h>
#include <string.h>

// last packet and interrupt handlers
volatile FPGAInPacket lastPacket;
void FPGACommIH();

FPGAComm* FPGAComm::getInstance()
{
	if(singleton.initialized) {
		return &singleton;
	}

	return NULL;
}

FPGAInPacket FPGAComm::getLastPacket()
{
	FPGAInPacket* returnPacket = (FPGAInPacket*)&lastPacket;
	return *returnPacket;
}

void FPGAComm::init(uint8 inPin, uint8 outPin, uint8 intPin, uint8 sendPin)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->interruptPin = intPin;
	this->sendPin = sendPin;

	// properly configure the pins
	pinMode(inPin, INPUT);

	pinMode(outPin, OUTPUT);
	pinMode(sendPin, OUTPUT);

	// attach the interrupt
	attachInterrupt(intPin, FPGACommIH, RISING);

	// zero out the last packet
	memset((FPGAInPacket*)(&lastPacket), 0, sizeof(FPGAInPacket));
}

void FPGAComm::deinit()
{
	detachInterrupt(this->interruptPin);

	this->initialized = false;
}

void FPGAComm::send(FPGAOutPacket outPacket)
{
	if (outPacket.testing) {
		digitalWrite(outPin, HIGH);
	}
	else {
		digitalWrite(outPin, LOW);
	}

	// bring the interrupt pin high, wait for .1 seconds, and bring down
	digitalWrite(sendPin, HIGH);
	delay(100);
	digitalWrite(sendPin, LOW);
}

void FPGAComm::receive(FPGAInPacket* inPacket)
{
	inPacket->testing = digitalRead(inPin);
}

// intterrupt handler
void FPGACommIH()
{
	// get an instance of the comm protocol
	FPGAComm* comm = FPGAComm::getInstance();

	comm->receive((FPGAInPacket*)&lastPacket);
}

#endif
