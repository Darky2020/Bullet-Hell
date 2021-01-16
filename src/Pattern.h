#pragma once

#include "main.h"
#include "Bullet.h"
#include "Player.h"

class Pattern
{
public:
	Pattern(int id, float x, float y, float start, float step, float dur, float ang, float vel, int rate, float accel, int rays, float spread, int bulletLifetime);
	~Pattern();

	int pattern_id;

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
	int bulletLifeTime;

	int lastSpawn;
	int firstSpawn;

	std::vector<Bullet*> Bullets;

	void UpdatePattern(Player* Player, SDL_Renderer* renderer, int LevelStartedAt);

	bool CanDeletePattern();

	int GetID();

	void ChangePattern(float x, float y, float step, float ang, float vel, int rate, float accel, int rays, float spread);
	
};