#ifndef TEST_H
#define TEST_H

extern volatile int newData;
extern volatile int pin5;

void comm_init();
void comm_handle();

#endif