#include "Main.h"

CMain::CMain()
{
	running = false;
	csdl_setup = new CSDL_Setup(&running);

	gameObjects = new GameObjects(csdl_setup->GetRenderer(), csdl_setup->GetEvent());
	// int id, float x, float y, float startAt, float step, float dur, float ang, float vel, int rate, float accel, int rays, float spread
	gameObjects->AddPattern(new Pattern(0, HEIGHT/2, HEIGHT/2, 0, 5, 100, 0, 5, 1, 0, 5, 360));
	gameObjects->AddTrigger(new Trigger(5000, 0, None, None, None, None, None, None, -0.1, None, None));
	gameObjects->AddTrigger(new Trigger(10000, 0, None, None, None, None, 2, None, 0, None, None));
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