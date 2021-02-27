#include "SDL_Setup.h"

CSDL_Setup::CSDL_Setup(bool* running)
{

	if (SDL_Init( SDL_INIT_EVERYTHING) < 0 )  
	{  
	    std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;  
	    *running = false;
	}  

	TTF_Init();

	Mix_Init(MIX_INIT_OGG);

	window = NULL;
	window = SDL_CreateWindow("Unnamed bullet hell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);  

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

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
    font = io.Fonts->AddFontFromFileTTF("packages/fonts/font.ttf", 25.f);
    fontPauseMenuTitle = io.Fonts->AddFontFromFileTTF("packages/fonts/font.ttf", 45.f);

    ImGuiSDL::Initialize(renderer, 1280, 720);
}

CSDL_Setup::~CSDL_Setup(void)
{
	ImGuiSDL::Deinitialize();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	ImGui::DestroyContext();
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

ImFont* CSDL_Setup::GetFont()
{
	return font;
}

ImFont* CSDL_Setup::GetFont2()
{
	return fontPauseMenuTitle;
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