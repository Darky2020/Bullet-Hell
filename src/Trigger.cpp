#include "SDL_Setup.h"
#include "Trigger.h"

Trigger::Trigger(int ExecTime, int targid, float x, float y, float step, float ang, float vel, int rate, float accel, int rays, float spread)
{
	ExecuteTime = ExecTime;
	targetID = targid;

	changeX = x;
	changeY = y;
	changeStep = step;
	changeAngle = ang;
	changeVelocity = vel;
	changeRate = rate;
	changeAcceleration = accel;
	changeRays = rays;
	changeSpread = spread;
}

Trigger::~Trigger() 
{

}

bool Trigger::CheckIfCanBeExecuted()
{
	if(SDL_GetTicks() >= ExecuteTime) return true;
	else return false;
}
