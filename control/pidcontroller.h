#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PidController
{
private:
	float kp, ki, kd;
	float setpoint;

	float lastPos;

public:
	PidController(float p, float i, float d);

	void setSetpoint(float setpoint);

	float calculate();
};

#endif
