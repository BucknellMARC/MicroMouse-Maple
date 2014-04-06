// Here's a wirish include:
#include <wirish/wirish.h>

#include "control/Ultrasonic.h"

PingUltrasonic ultrasonic = PingUltrasonic(0);

void setup(void) {
}

void loop(void) {

	SerialUSB.println("Reading ultrasonic...");

	int outValue = ultrasonic.readValue();

	SerialUSB.print("Ultrasonic: ");
	SerialUSB.print(outValue);
	SerialUSB.println(" usecs");

	// delay 1 second
	delayMicroseconds(100000);
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
