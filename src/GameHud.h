#pragma once
#include "main.h"
#include "Sprite.h"
#include "Text.h"
#include "SDL_Setup.h"

class GameHud
{
public:
	GameHud(SDL_Renderer* Renderer);
	~GameHud();

	void DrawBG();
	void DrawHealth(int health);
	void UpdateImgui(CSDL_Setup* csdl_setup);

	SDL_Renderer* renderer;

	CSprite* heart1;
	CSprite* heart2;
	CSprite* heart3;

	CText* HealthText;
	
};