
#pragma once
#include "main.h"
#include "Sprite.h"

class Player
{
public:
	Player(SDL_Renderer* renderer, SDL_Event* event, int x, int y);
	~Player();

	int PosX;
	int PosY;

	CSprite* sprite;

	SDL_Event* Event;

	void DrawPlayer();
	void Move();
	void UpdatePlayer();

	float speed;

	float PlayerSpriteWidth;
	float PlayerSpriteHeight;

	const Uint8 *state;

	float centerX;
	float centerY;

	int HitAtTime;

	float returnPlayerCenterX();
	float returnPlayerCenterY();
	float returnPlayerPosX();
	float returnPlayerPosY();

	int returnPlayerHealt() {return health;}

	void GotHit();

	bool isInvulnerable;
	bool CheckIfInvulnerable();

	int health;
};