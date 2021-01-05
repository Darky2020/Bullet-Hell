#pragma once
#include "SDL_Setup.h"
#include "main.h"
#include "Pattern.h"
#include "GameObjects.h"
#include "Trigger.h"

class CMain
{
public:
	CMain();
	~CMain(void);

	bool running;

	const int FPS = 60;
	const int frameDelay = 1000/FPS;
	Uint32 frameStart;
	int frameTime;

	void GameLoop();
private:
	CSDL_Setup* csdl_setup;
	GameObjects* gameObjects;
};