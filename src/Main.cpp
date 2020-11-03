#include "Main.h"

CMain::CMain()
{
	running = false;
	csdl_setup = new CSDL_Setup(&running);

	Patterns.push_back(new Pattern(HEIGHT/2, HEIGHT/2, 0, 7, 10, 0, 5, 1, 0.05, 7, 360));
	Patterns.push_back(new Pattern(HEIGHT/2, HEIGHT/2, 10, 7, 10, 0, 5, 1, 0.05, 3, 360));

	heart1 = new CSprite(csdl_setup->GetRenderer(), "packages/icons/heart_icon.png", HEIGHT+20, 100, 48, 48, 0);
	heart2 = new CSprite(csdl_setup->GetRenderer(), "packages/icons/heart_icon.png", HEIGHT+70, 100, 48, 48, 0);
	heart3 = new CSprite(csdl_setup->GetRenderer(), "packages/icons/heart_icon.png", HEIGHT+120, 100, 48, 48, 0);

	player = new Player(csdl_setup->GetRenderer(), csdl_setup->GetEvent(), 400, 600);

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

		// float x1 = (float)player->returnPlayerCenterX()-(2*HEIGHT_MULTIPLIER);
		// float y1 = (float)player->returnPlayerCenterY()-(2*HEIGHT_MULTIPLIER);

		// hitbox.x = x1;
		// hitbox.y = y1;
		// hitbox.w = 4*HEIGHT_MULTIPLIER;
  //       hitbox.h = 4*HEIGHT_MULTIPLIER;

		// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		// SDL_RenderFillRect(renderer, &hitbox);
		// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		SDL_Rect rect;
		rect.x = HEIGHT;
        rect.y = 0;
        rect.w = HEIGHT;
        rect.h = HEIGHT;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &rect);

		rect.x = HEIGHT;
        rect.y = 0;
        rect.w = 3;
        rect.h = HEIGHT;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		rect.x = HEIGHT+6;
        rect.y = 0;
        rect.w = 3;
        rect.h = HEIGHT;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		if(player->returnPlayerHealt() > 0) heart1->Draw();
		if(player->returnPlayerHealt() > 1) heart2->Draw();
		if(player->returnPlayerHealt() > 2) heart3->Draw();

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