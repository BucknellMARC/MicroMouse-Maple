// Here's a wirish include:
#include <wirish/wirish.h>

#include "fpga-comm/FPGAComm.h"

FPGAComm* comm;

void setup(void) {
	
	// init the FPGA comm
	comm = FPGAComm::getInstance();

	FPGAPinInLayout inLayout;
	inLayout.leftWall = D0;
	inLayout.frontWall = D1;
	inLayout.rightWall = D2;
	inLayout.interrupt = D13;

	FPGAPinOutLayout outLayout;
	outLayout.drive = D6;
	outLayout.turn = D7;
	outLayout.dataStart = D8;
	outLayout.interrupt = D12;

	comm->init(inLayout, outLayout);

	pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop(void) {

	if (comm->isNewData()) {
		SerialUSB.println("Found new data!");

		FPGAInPacket packet = comm->getLastPacket();

		SerialUSB.print("LeftWall: ");
		SerialUSB.println(packet.leftWall);

		SerialUSB.print("FrontWall: ");
		SerialUSB.println(packet.frontWall);

		SerialUSB.print("RightWall: ");
		SerialUSB.println(packet.rightWall);
	}
	else {
		SerialUSB.println("No new data");
	}

	//toggleLED();
	digitalWrite(BOARD_LED_PIN, LOW);
	delay(250);
}

// Standard libmaple init() and main.
//
// The init() part makes sure your board gets set up correctly. It's
// best to leave that alone unless you know what you're doing. main()
// is the usual "call setup(), then loop() forever", but of course can
// be whatever you want.

__attribute__((constructor)) void premain() {
    init();
}

int main(void) {
    setup();

    while (true) {
        loop();
    }

    return 0;
}
