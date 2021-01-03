#pragma once
#include "SDL_Setup.h"
#include "main.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Pattern.h"
#include "Player.h"
#include "GameHud.h"

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

	void GameLoop();
	Pattern* GetPatternByID(int id);
private:
	CSDL_Setup* csdl_setup;
	GameHud* gameStats;
	std::vector<Pattern*> Patterns;

	Player* player;
};