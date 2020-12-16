#include "Main.h"

CMain::CMain()
{
	running = false;
	csdl_setup = new CSDL_Setup(&running);

	Patterns.push_back(new Pattern(HEIGHT/2, HEIGHT/2, 0, 7, 10, 0, 5, 1, 0.05, 7, 360));
	Patterns.push_back(new Pattern(HEIGHT/2, HEIGHT/2, 10, 7, 10, 0, 5, 1, 0, 90, 360));

	player = new Player(csdl_setup->GetRenderer(), csdl_setup->GetEvent(), 400, 600);

	gameStats = new GameStats(csdl_setup->GetRenderer());

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

		player->UpdatePlayer();

		// SDL_Rect hitbox;

		// float x1 = (float)player->returnPlayerCenterX()-2;
		// float y1 = (float)player->returnPlayerCenterY()-2;

		/////////////////// Plan to add an option to toggle it

		// hitbox.x = x1;
		// hitbox.y = y1;
		// hitbox.w = 4;
        // hitbox.h = 4;

		// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		// SDL_RenderFillRect(renderer, &hitbox);
		// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

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