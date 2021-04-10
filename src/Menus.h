#pragma once
#include "main.h"
#include "SDL_Setup.h"
#include "GameObjects.h"

class Menus
{
public:
	Menus();
	~Menus();
	
	void DrawMainMenu(bool *running, int *MenuState, GameObjects *gameObjects);
	void Update(bool *running, int *MenuState,GameObjects *gameObjects);

};