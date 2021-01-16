#pragma once

#include "main.h"
#include "Sprite.h"
#include "Player.h"

class Bullet
{
public:
	Bullet(Player* Player, SDL_Renderer* renderer, float sourceX, float sourceY, float angle, float velocity, float accel, int CreatedAt, int Lifetime);
	~Bullet();
	auto calculate_distance (float X, float Y, float ang, float vel);

	void DrawBullet();

	void UpdateBullet();

	void MoveBullet();

	bool CheckIfOutOfBounds();
	bool CheckIfLifetimeIsOver(int CurrentTime);
	bool CheckIfCollidedWithPlayer(float circleX, float circleY, float circleR, float rectX, float rectY, float rectW, float rectH);

	float sourceX;
	float sourceY;
	float angle;
	float velocity;
	float acceleration;

	int CreatedAtTime;
	int LifeTime;

	float width;
	float height;

	CSprite* sprite;
	Player* player;
};