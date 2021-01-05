#pragma once

#include "main.h"

class Trigger
{
public:
	Trigger(int ExecTime, int targid, float x, float y, float step, float ang, float vel, int rate, float accel, int rays, float spread);
	~Trigger();

	int ExecuteTime;
	int targetID;
	float changeX;
	float changeY;
	float changeStep;
	float changeAngle;
	float changeVelocity;
	int changeRate;
	float changeAcceleration;
	int changeRays;
	float changeSpread;

	int GetTargetID() { return targetID; }
	float GetChangeX() { return changeX; }
	float GetChangeY() { return changeY; }
	float GetChangeStep() { return changeStep; }
	float GetChangeAngle() { return changeAngle; }
	float GetChangeVelocity() { return changeVelocity; }
	int GetChangeRate() { return changeRate; }
	float GetChangeAcceleration() { return changeAcceleration; }
	int GetChangeRays() { return changeRays; }
	float GetChangeSpread() { return changeSpread; }

	bool CheckIfCanBeExecuted();
};