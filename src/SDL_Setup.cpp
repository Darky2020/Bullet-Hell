#include "SDL_Setup.h"

CSDL_Setup::CSDL_Setup(bool* running)
{

	if (SDL_Init( SDL_INIT_EVERYTHING ) < 0 )  
	{  
	    std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;  
	    *running = false;
	}  

	window = NULL;
	window =  SDL_CreateWindow("Unnamed bullet hell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);  

	if(window == NULL)
	{
		std::cout << "Could not create window! SDL error: " << SDL_GetError() << std::endl;  
		*running = false;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	SDL_RenderSetLogicalSize(renderer, 1280, 720); 

	if(renderer == NULL)
	{
		std::cout << "Could not create renderer! SDL error" << SDL_GetError() << std::endl;  
		*running = false;
	}

	event = new SDL_Event();

	if(window != NULL && renderer != NULL)
	{
		*running = true;
	}
}

CSDL_Setup::~CSDL_Setup(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete event;
}

SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::GetEvent()
{
	return event;
}

SDL_Window* CSDL_Setup::GetWindow()
{
	return window;
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(event);
	SDL_RenderClear(renderer);
}

void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}