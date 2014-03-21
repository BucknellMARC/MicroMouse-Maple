struct FPGAInPacket
{
	bool leftWall;
	bool rightWall;
	bool frontWall;
};

struct FPGAOutPacket
{
	Direction direction;

};

class FPGAComm
{
	// Private Members
private:
	FPGAComm singleton;
	volatile FPGAInPacket lastPacket;

	bool initialized;

	uint8 inPin;
	uint8 outPin;
	uint8 intPin;

private:
	FPGAComm();
	~FPGAComm();

public:
	FPGAComm getInstance();
	FPGAInPacket getLastPacket();

	void init(uint8 inPin, uint8 outPin, uint8i intPin);
	void deinit();

	void send(FPGAOutPacket outPacket);
};