// Here's a wirish include:
#include <wirish/wirish.h>

#include "fpga-comm/test.h"

void setup(void) {
	// init the FPGA comm and bind interrupt
	comm_init();

    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop(void) {
	if (newData) {
		// print out the information
		SerialUSB.println("Interrupt Triggered!\n");
		SerialUSB.print("Pin 5: ");
		SerialUSB.print(pin5);
		SerialUSB.println();

		newData = 0;
	}
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
