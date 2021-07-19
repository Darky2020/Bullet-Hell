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

	void ImGui_SDL2_ProcessEvent(const SDL_Event* event);
	
	void Begin();
	void End();

	int lastWheelScrollTimestamp;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event;
};