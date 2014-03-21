#ifndef FPGA_COMM_CPP
#define FPGA_COMM_CPP

#include "FPGAComm.h"

#include <wirish/wirish.h>
#include <string.h>

// declare the singleton object
FPGAComm FPGAComm::singleton;

// last packet and interrupt handlers
volatile FPGAInPacket lastPacket;
void FPGACommIH();

FPGAComm* FPGAComm::getInstance()
{
	return &singleton;
}

FPGAInPacket FPGAComm::getLastPacket()
{
	newData = false;

	FPGAInPacket* returnPacket = (FPGAInPacket*)&lastPacket;
	return *returnPacket;
}

void FPGAComm::init(FPGAPinInLayout inLayout, FPGAPinOutLayout outLayout)
{
	in = inLayout;
	out = outLayout;

	// configure the inputs
	pinMode(in.leftWall, INPUT);
	pinMode(in.frontWall, INPUT);
	pinMode(in.rightWall, INPUT);

	// attach the interrupt
	pinMode(in.interrupt, INPUT);
	attachInterrupt(in.interrupt, FPGACommIH, RISING);

	// configure the outputs
	pinMode(out.drive, OUTPUT);
	pinMode(out.turn, OUTPUT);
	
	pinMode(out.dataStart, OUTPUT);
	pinMode(out.dataStart + 1, OUTPUT);
	pinMode(out.dataStart + 2, OUTPUT);
	pinMode(out.dataStart + 3, OUTPUT);
	
	pinMode(out.interrupt, OUTPUT);

	// zero out the last packet
	memset((FPGAInPacket*)(&lastPacket), 0, sizeof(FPGAInPacket));
}

void FPGAComm::deinit()
{
	detachInterrupt(in.interrupt);

	this->initialized = false;
}

void FPGAComm::send(FPGAOutPacket outPacket)
{
	// write the command
	if (outPacket.drive) {
		digitalWrite(out.drive, HIGH);
		digitalWrite(out.turn, LOW);
	}
	else {
		digitalWrite(out.drive, LOW);
		digitalWrite(out.turn, HIGH);
	}

	// write the data
	for (int n = 0; n < 4; n++) {
		if ((outPacket.data >> n) & 1) {
			digitalWrite(out.dataStart + n, HIGH);
		}
		else {
			digitalWrite(out.dataStart + n, LOW);
		}
	}

	// bring int high, allow time to settle
	digitalWrite(out.interrupt, HIGH);
	delay(100);
	digitalWrite(out.interrupt, LOW);
}

void FPGAComm::receive(FPGAInPacket* inPacket)
{
	inPacket->leftWall = digitalRead(in.leftWall);
	inPacket->frontWall = digitalRead(in.frontWall);
	inPacket->rightWall = digitalRead(in.rightWall);

	newData = true;
}

volatile bool FPGAComm::isNewData()
{
	return newData;
}

// intterrupt handler
void FPGACommIH()
{
	// get an instance of the comm protocol
	FPGAComm* comm = FPGAComm::getInstance();

	comm->receive((FPGAInPacket*)&lastPacket);

	digitalWrite(BOARD_LED_PIN, HIGH);

	return;
}

#endif
