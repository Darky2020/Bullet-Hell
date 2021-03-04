#pragma once
#include "main.h"
#include "Sprite.h"
#include "SDL_Setup.h"

class GameHud
{
public:
	GameHud(SDL_Renderer* Renderer);
	~GameHud();

	void DrawBG();
	void DrawStats(int health, int NumberOfBullets);
	void UpdateImgui(CSDL_Setup* csdl_setup);

	SDL_Renderer* renderer;
	
};