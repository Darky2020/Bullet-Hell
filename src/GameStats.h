#pragma once
#include "main.h"
#include "Sprite.h"
#include "Text.h"

class GameStats
{
public:
	GameStats(SDL_Renderer* Renderer);
	~GameStats();

	void DrawBG();

	void DrawHearts(int health);

	SDL_Renderer* renderer;

	CSprite* heart1;
	CSprite* heart2;
	CSprite* heart3;

	CText* HealthText;
	
};