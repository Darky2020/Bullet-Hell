#include "Pattern.h"

Pattern::Pattern(int id, float x, float y, float startAt, float step, float dur, float ang, float vel, int rate, float accel, int rays, float spread)
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

	lastSpawn = 0;
	firstSpawn = SDL_GetTicks();
}

Pattern::~Pattern()
{
	// std::vector<Bullet*>::iterator BulletIterator;
	// int index = 0;

	// for(BulletIterator = Bullets.begin(); BulletIterator != Bullets.end();)
	// {
	// 	delete Bullets[index];
	// 	Bullets[index] = NULL;
	// 	BulletIterator = Bullets.erase(BulletIterator); 
	// 	index+=1;
	// }
}

void Pattern::UpdatePattern(Player* Player, SDL_Renderer* renderer)
{
	std::vector<Bullet*>::iterator BulletIterator;
	int index = 0;

	for(BulletIterator = Bullets.begin(); BulletIterator != Bullets.end();)
	{
		Bullets[index]->UpdateBullet(); 
		if(Bullets[index]->CheckIfOutOfBounds())
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

	if(SDL_GetTicks() - lastSpawn > FireRate && SDL_GetTicks() - firstSpawn < duration && SDL_GetTicks() >= startAtTime)
		{

			float offset = 0;
			if(NumOfRays == 1) offset = 0;
			else if(PatternSpread == 360) offset = (PatternSpread/(NumOfRays));
			else offset = (PatternSpread/(NumOfRays-1));

			for(int i = 0; i < NumOfRays; i++)
			{	

				Bullets.push_back(new Bullet(Player, renderer, sourceX, sourceY, angle+(offset*i), velocity, acceleration));
			}

			angle += angleStep;
			lastSpawn = SDL_GetTicks();
		}
}

bool Pattern::CanDeletePattern()
{
	if(SDL_GetTicks() - firstSpawn > duration && Bullets.size() == 0) return true;
	else return false;
}

int Pattern::GetID()
{
	return pattern_id;
}

void Pattern::ChangePattern(float x, float y, float step, float ang, float vel, int rate, float accel, int rays, float spread)
{
	if(x != NULL)      sourceX = x;
	if(y != NULL)      sourceY = y;
	if(step != NULL)   angleStep = step;
	if(ang != NULL)    angle = ang;
	if(vel != NULL)    velocity = vel;
	if(rate != NULL)   FireRate = rate;
	if(accel != NULL)  acceleration = accel;
	if(rays != NULL)   NumOfRays = rays;
	if(spread != NULL) PatternSpread = spread;
}