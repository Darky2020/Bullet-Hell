
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

	void Reset();
	void DrawPlayer();
	void Move();
	void UpdatePlayer(int LevelStartedAt, bool paused);

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

	int returnPlayerHealth() {return health;}

	void GotHit(int LevelStartedAt);

	bool isInvulnerable;
	bool CheckIfInvulnerable();

	int health;
};