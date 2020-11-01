#include "main.h"
#include "Bullet.h"
#include "Player.h"

class Pattern
{
public:
	Pattern(float x, float y, float start, float step, float dur, float ang, float vel, int rate, float accel, int rays, float spread);
	~Pattern();

	float sourceX;
	float sourceY;
	float duration;
	float angle;
	float velocity;
	int FireRate;
	float acceleration;
	float startAtTime;
	float angleStep;
	int NumOfRays;
	float PatternSpread;

	int lastSpawn;
	int firstSpawn;

	std::vector<Bullet*> Bullets;

	void UpdatePattern(Player* Player, SDL_Renderer* renderer);

	bool CanDeletePattern();
	
};