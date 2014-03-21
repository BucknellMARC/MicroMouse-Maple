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
	//return (FPGAInPacket)lastPacket;

	FPGAInPacket p;
	return p;

}

void FPGAComm::init(uint8 inPin, uint8 outPin, uint8 intPin)
{
	this->inPin = inPin;
	this->outPin = outPin;
	this->interruptPin = intPin;

	// properly configure the pins
	pinMode(inPin, INPUT);
	pinMode(outPin, OUTPUT);

	// attach the interrupt
	attachInterrupt(intPin, FPGACommIH, RISING);
}

void FPGAComm::deinit()
{
	detachInterrupt(this->interruptPin);

	this->initialized = false;
}

void FPGAComm::send(FPGAOutPacket outPacket)
{

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

	FPGAInPacket inPacket;
	comm->receive(&inPacket);

	//comm->receive(&lastPacket);
}

#endif
