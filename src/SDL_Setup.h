#pragma once
#include "main.h"

class CSDL_Setup
{
public:
	CSDL_Setup(bool* running);
	~CSDL_Setup(void);

	SDL_Renderer* GetRenderer();
	SDL_Event* GetEvent();
	SDL_Window* GetWindow();
	ImFont* GetFont();
	ImFont* GetFont2();

	void Begin();
	void End();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event;

	ImFont* font;
	ImFont* fontPauseMenuTitle;
};