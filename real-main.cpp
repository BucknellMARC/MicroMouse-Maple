// Here's a wirish include:
#include <wirish/wirish.h>

// setup() and loop():
static const int BUFFER_SIZE = 256;
char input;
char inputBuffer[BUFFER_SIZE];
int bufferLoc = 0;

void setup(void) {
    pinMode(BOARD_LED_PIN, OUTPUT);
}

void loop(void) {
	// echoes whatever is written to the screen
	SerialUSB.read(&input, 1);
	SerialUSB.write(&input, 1);
	//SerialUSB.print((int)input);

	// check for newline
	if (input == '\r') {
		SerialUSB.print('\n');
		SerialUSB.write("-> ", 3);

		bufferLoc = 0;
	}
	else if (input == 127) {
		// blank out the buffer
		SerialUSB.print('\r');
		for (int n = 0; n < (bufferLoc + 3); n++) {
			SerialUSB.write(" ", 1);
		}

		bufferLoc--;
		if (bufferLoc < 0) {
			bufferLoc = 0;
		}

		SerialUSB.print('\r');
		SerialUSB.write("-> ", 3);
		SerialUSB.write(inputBuffer, bufferLoc);
	}
	// else, add to the buffer
	else if (bufferLoc < BUFFER_SIZE) {
		inputBuffer[bufferLoc++] = input;
	}
	else {
		bufferLoc = 0;
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
