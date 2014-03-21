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
	static FPGAComm singleton;

public:
	FPGAComm();

	void send(FPGAOutPacket outPacket);
	FPGAInPacket recieve();

	~FPGAComm();
};