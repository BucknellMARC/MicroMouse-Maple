#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

class PIDController
{
private:
	float kp, ki, kd;
	float setpoint;

	float i;

	float lastPos;

public:
	PIDController(float p, float i, float d);

	void setSetpoint(float setpoint);

	float calculate();

	~PIDController();
};

#endif
