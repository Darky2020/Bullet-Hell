#include "Pattern.h"

Pattern::Pattern(int id, float x, float y, float startAt, float step, float dur, float ang, float vel, int rate, float accel, int rays, float spread, int bulletLifetime)
{
	pattern_id = id;

	sourceX = x;
	sourceY = y;
	angle = ang;
	velocity = vel;
	FireRate = rate*100;
	acceleration = accel;
	startAtTime = startAt*1000;
	duration = dur*1000+startAtTime;
	angleStep = step;
	NumOfRays = rays;
	PatternSpread = spread;
	bulletLifeTime = bulletLifetime;

	lastSpawn = 0;
}

Pattern::~Pattern()
{

}

void Pattern::UpdatePattern(Player* Player, SDL_Renderer* renderer, int LevelStartedAt, bool paused)
{
	std::vector<Bullet*>::iterator BulletIterator;
	int index = 0;

	for(BulletIterator = Bullets.begin(); BulletIterator != Bullets.end();)
	{
		Bullets[index]->UpdateBullet(LevelStartedAt, paused); 
		if((Bullets[index]->CheckIfOutOfBounds() || Bullets[index]->CheckIfLifetimeIsOver(SDL_GetTicks()-LevelStartedAt)) && !paused)
		{
			delete Bullets[index];
			Bullets[index] = NULL;
			BulletIterator = Bullets.erase(BulletIterator); 
		}
		else
		{
			++BulletIterator;
	 		index++;
		}
	}

	if(SDL_GetTicks()-LevelStartedAt - lastSpawn > FireRate && SDL_GetTicks()-LevelStartedAt < duration && SDL_GetTicks()-LevelStartedAt >= startAtTime && !paused)
	{
		float offset = 0;
		if(NumOfRays == 1) offset = 0;
		else if(PatternSpread == 360) offset = (PatternSpread/(NumOfRays));
		else offset = (PatternSpread/(NumOfRays-1));

		for(int i = 0; i < NumOfRays; i++)
		{	
			Bullets.push_back(new Bullet(Player, renderer, sourceX, sourceY, angle+(offset*i), velocity, acceleration, (SDL_GetTicks()-LevelStartedAt), bulletLifeTime));
		}

		angle += angleStep;
		lastSpawn = SDL_GetTicks()-LevelStartedAt;
	}
}

bool Pattern::CanDeletePattern(int LevelStartedAt)
{
	if(SDL_GetTicks()-LevelStartedAt > duration && Bullets.size() == 0) return true;
	else return false;
}

int Pattern::GetID()
{
	return pattern_id;
}

void Pattern::ChangePattern(float x, float y, float step, float ang, float vel, int rate, float accel, int rays, float spread, int bulletLifetime)
{
	if(x != None)      sourceX = x;
	if(y != None)      sourceY = y;
	if(step != None)   angleStep = step;
	if(ang != None)    angle = ang;
	if(vel != None)    velocity = vel;
	if(rate != None)   FireRate = rate*100;
	if(accel != None)  acceleration = accel;
	if(rays != None)   NumOfRays = rays;
	if(spread != None) PatternSpread = spread;
	if(bulletLifetime) bulletLifeTime = bulletLifetime;
}