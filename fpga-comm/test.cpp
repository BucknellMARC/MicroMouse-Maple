#ifndef TEST_C
#define TEST_C

#include <wirish/wirish.h>

#include "test.h"

// will hold status of whether or not the pin has been pressed
volatile int newData;
volatile int pin5;

void comm_init()
{
	pin5 = LOW;

	// open D5 for reading
	pinMode(D5, INPUT);

	// attach interrupt on pin 6
	attachInterrupt(D6, comm_handle, RISING);
}

void comm_handle()
{
	newData = 1;

	// read the pin from D5
	pin5 = digitalRead(D5);
}

#endif