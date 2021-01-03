#pragma once
#include "main.h"
#include "Sprite.h"
#include "Text.h"

class GameHud
{
public:
	GameHud(SDL_Renderer* Renderer);
	~GameHud();

	void DrawBG();

	void DrawHearts(int health);

	SDL_Renderer* renderer;

	CSprite* heart1;
	CSprite* heart2;
	CSprite* heart3;

	CText* HealthText;
	
};