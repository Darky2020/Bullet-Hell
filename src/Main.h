#pragma once
#include "SDL_Setup.h"
#include "main.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Pattern.h"
#include "Player.h"

class CMain
{
public:
	CMain();
	~CMain(void);

	bool running;

	bool clicked;

	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 frameStart;
	int frameTime;

	float HEIGHT_MULTIPLIER;
	float WIDTH_MULTIPLIER;


	void GameLoop();
private:
	CSDL_Setup* csdl_setup;
	std::vector<Pattern*> Patterns;

	Player* player;
	CSprite* heart1;
	CSprite* heart2;
	CSprite* heart3;
};