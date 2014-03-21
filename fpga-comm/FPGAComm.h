#ifndef FPGA_COMM_H
#define FPGA_COMM_H

#include <wirish/wirish.h>

struct FPGAInPacket
{
	int leftWall;
	int rightWall;
	int frontWall;
};

struct FPGAOutPacket
{
	bool drive;
	bool turn;

	uint8 data;
};

struct FPGAPinInLayout {
	uint8 leftWall;			// HIGH if there is a wall
	uint8 frontWall;		//
	uint8 rightWall;		//

	uint8 interrupt;
};

struct FPGAPinOutLayout {
	uint8 drive;			// drive command pin
	uint8 turn;				// turn command pin
	uint8 dataStart;		// start of 4 sequential data pins

	uint8 interrupt;
};

class FPGAComm
{
private:
	static FPGAComm singleton;

	bool initialized;
	volatile bool newData;

	FPGAPinInLayout in;
	FPGAPinOutLayout out;

public:
	static FPGAComm* getInstance();
	FPGAInPacket getLastPacket();

	void init(FPGAPinInLayout inLayout, FPGAPinOutLayout outLayout);
	void deinit();

	void send(FPGAOutPacket outPacket);
	void receive(FPGAInPacket* inPacket);
	volatile bool isNewData();
};

#endif
