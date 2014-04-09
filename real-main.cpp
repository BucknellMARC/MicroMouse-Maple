// Here's a wirish include:
#include <wirish/wirish.h>

#include "control/Motor.h"

Motor motor = Motor(#pin1, #pin2, #pin3);

void setup(void) {
	SerialUSB.println("Starting motor test program");
}

void loop(void) {
	SerialUSB.println("Motor test loop");
	motor.setPower(0.5f);
	delay(2500);
	motor.setPower(0f);
	delay(2500);
	motor.setPower(1.0f);
	delay(2500);
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
