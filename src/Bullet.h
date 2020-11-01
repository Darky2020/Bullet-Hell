#pragma once

#include "main.h"
#include "Sprite.h"
#include "Player.h"

class Bullet
{
public:
	Bullet(Player* Player, SDL_Renderer* renderer, float sourceX, float sourceY, float angle, float velocity, float accel);
	~Bullet();
	auto calculate_distance (float X, float Y, float ang, float vel);

	void DrawBullet();

	void UpdateBullet();

	void MoveBullet();

	bool CheckIfOutOfBounds();
	bool CheckIfCollidedWithPlayer(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	float sourceX;
	float sourceY;
	float angle;
	float velocity;
	float acceleration;

	float width;
	float height;

	float HEIGHT_MULTIPLIER;
	float WIDTH_MULTIPLIER;

	CSprite* sprite;
	Player* player;


};