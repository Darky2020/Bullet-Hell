#include "Main.h"
#include "SDL_DrawCircle.h"

CMain::CMain()
{
	running = false;
	csdl_setup = new CSDL_Setup(&running);
	// int id, float x, float y, float startAt, float step, float dur, float ang, float vel, int rate, float accel, int rays, float spread
	Patterns.push_back(new Pattern(0, HEIGHT/2, HEIGHT/2, 0, 5, 100, 0, 5, 1, 0, 5, 360));

	player = new Player(csdl_setup->GetRenderer(), csdl_setup->GetEvent(), 400, 600);

	gameStats = new GameHud(csdl_setup->GetRenderer());

}

CMain::~CMain(void)
{

}

Pattern* CMain::GetPatternByID(int id)
{
	std::vector<Pattern*>::iterator PatternIterator;
	int index = 0;

	for(PatternIterator = Patterns.begin(); PatternIterator != Patterns.end();)
	{
		if(Patterns[index]->GetID() == id)
		{
			return Patterns[index];
		}
		else
		{
			++PatternIterator;
	 		index++;
		}
	}

	return NULL;
}

void CMain::GameLoop()
{
	while(running && csdl_setup->GetEvent()->type != SDL_QUIT)
	{
		frameStart = SDL_GetTicks();
		csdl_setup->Begin();


		SDL_Renderer* renderer = csdl_setup->GetRenderer();
		SDL_Window* window = csdl_setup->GetWindow();

		// if(csdl_setup->GetEvent()->type == SDL_MOUSEBUTTONDOWN) {
		// 	if(csdl_setup->GetEvent()->button.button == SDL_BUTTON_LEFT && !clicked)
		// 	{
		// 	SDL_GetMouseState(&MouseX, &MouseY);
		// 	}
  //   	}

		std::vector<Pattern*>::iterator PatternIterator;
		int index = 0;

		for(PatternIterator = Patterns.begin(); PatternIterator != Patterns.end();)
		{
			Patterns[index]->UpdatePattern(player, renderer); 
			if(Patterns[index]->CanDeletePattern())
			{
				delete Patterns[index];
				Patterns[index] = NULL;
				PatternIterator = Patterns.erase(PatternIterator); 
			}
			else
			{
				++PatternIterator;
		 		index++;
			}
		}

		if(SDL_GetTicks() > 5000 && SDL_GetTicks() > 5100) GetPatternByID(0)->ChangePattern(NULL, NULL, -13, NULL, NULL, NULL, NULL, NULL, NULL);

		player->UpdatePlayer();

		int x1 = (int)player->returnPlayerCenterX();
		int y1 = (int)player->returnPlayerCenterY();

		///////////////// Plan to add an option to toggle it

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderFillCircle(renderer, x1, y1, 5);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		
		///////////////////

		gameStats->DrawBG();
		gameStats->DrawHearts(player->returnPlayerHealth());

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