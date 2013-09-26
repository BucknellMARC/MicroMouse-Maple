// Here's a wirish include:
#include <wirish/wirish.h>

// setup() and loop():

void setup(void) {
    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop(void) {
    SerialUSB.println("Hello World!");
    delay(1000);
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
