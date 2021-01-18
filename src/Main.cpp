#include "Main.h"

CMain::CMain()
{
	running = false;
	csdl_setup = new CSDL_Setup(&running);

	gameObjects = new GameObjects(csdl_setup->GetRenderer(), csdl_setup->GetEvent());

	gameObjects->LoadLevel("Test");
}

CMain::~CMain(void)
{

}

void CMain::GameLoop()
{
	while(running && csdl_setup->GetEvent()->type != SDL_QUIT)
	{
		frameStart = SDL_GetTicks();
		csdl_setup->Begin();

		SDL_Renderer* renderer = csdl_setup->GetRenderer();
		SDL_Window* window = csdl_setup->GetWindow();

		gameObjects->UpdateGameObjects();

		SDL_RenderPresent(renderer);
	    SDL_UpdateWindowSurface(window); 

		csdl_setup->End();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}