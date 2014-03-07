// Here's a wirish include:
#include <wirish/wirish.h>

// setup() and loop():
static const int BUFFER_SIZE = 256;
char input;
char inputBuffer[BUFFER_SIZE];
int bufferLoc = 0;

extern "C" {
	#include <logic/Robot.h>
}

Robot embeddedRobot;

volatile int numTimes;
volatile int state = LOW;


// this function runs interrupt code...
void interruptFunc()
{
	numTimes++;

	if (state == LOW) {
		state = HIGH;
	}
	else {
		state = LOW;
	}
	digitalWrite(BOARD_LED_PIN, state);

	return;
}

void setup(void) {
    pinMode(BOARD_LED_PIN, OUTPUT);

    embeddedRobot = robot_create(0, 0);

    // bind the interrupt
    pinMode(BOARD_BUTTON_PIN, INPUT);
    attachInterrupt(BOARD_BUTTON_PIN, interruptFunc, RISING);
}

void loop(void) {
	SerialUSB.println(numTimes);
	//SerialUSB.println("Testing123");
	//SerialUSB.print("Robot X: "); SerialUSB.print(embeddedRobot.xPos);
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
