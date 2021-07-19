#include "MainClass.h"
#include "Fonts.h"

CMain::CMain()
{
	running = false;
	csdl_setup = new CSDL_Setup(&running);

	gameObjects = new GameObjects(csdl_setup->GetRenderer(), csdl_setup->GetEvent());
	menus = new Menus();

	MenuState = MENUSTATE_MAINMENU;
}

CMain::~CMain(void)
{

}

void CMain::GameLoop()
{
	SDL_Event *ev = csdl_setup->GetEvent();
	while(running && ev->type != SDL_QUIT)
	{
		frameStart = SDL_GetTicks();
		csdl_setup->Begin();

		SDL_Renderer* renderer = csdl_setup->GetRenderer();
		SDL_Window* window = csdl_setup->GetWindow();

		csdl_setup->ImGui_SDL2_ProcessEvent(ev);

		ImGui::NewFrame();

		ImGui::PushFont(Fonts[DEFAULT_FONT]);

		if(MenuState == MENUSTATE_MAINMENU)
		{
			menus->Update(&running, &MenuState, gameObjects);
		}
		else if(MenuState == MENUSTATE_INGAME)
		{
			gameObjects->UpdateGameObjects(csdl_setup, &MenuState);
		}

		ImGui::PopFont();

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData()); 

	    SDL_UpdateWindowSurface(window);

		csdl_setup->End();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}