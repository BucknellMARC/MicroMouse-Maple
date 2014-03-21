#ifndef FPGA_COMM_H
#define FPGA_COMM_H

#include <wirish/wirish.h>

struct FPGAInPacket
{
	int leftWall;
	int rightWall;
	int frontWall;

	int testing;
};

struct FPGAOutPacket
{
	//Direction direction;
	int testing;
};

class FPGAComm
{
private:
	static FPGAComm singleton;

	bool initialized;

	uint8 inPin;
	uint8 outPin;
	uint8 interruptPin;

public:
	static FPGAComm* getInstance();
	FPGAInPacket getLastPacket();

	void init(uint8 inPin, uint8 outPin, uint8 intPin);
	void deinit();

	void send(FPGAOutPacket outPacket);
	void receive(FPGAInPacket* inPacket);
};

#endif
