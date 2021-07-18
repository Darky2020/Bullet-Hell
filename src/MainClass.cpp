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

void CMain::UpdateImgui(CSDL_Setup* csdl_setup) {
	ImGuiIO& io = ImGui::GetIO();

	if (csdl_setup->GetEvent()->type == SDL_WINDOWEVENT)
	{
		if (csdl_setup->GetEvent()->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			io.DisplaySize.x = static_cast<float>(csdl_setup->GetEvent()->window.data1);
			io.DisplaySize.y = static_cast<float>(csdl_setup->GetEvent()->window.data2);
		}
	}

	int mouseX, mouseY;
	const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

	int wX, wY;
	SDL_GetWindowSize(csdl_setup->GetWindow(), &wX, &wY);

	float scaleX, scaleY;
	scaleX = 1280.f/(float)wX;
	scaleY = 720.f/(float)wY;
	
	io.DeltaTime = 1.0f / 60.0f;
	io.MousePos = ImVec2(static_cast<float>(mouseX*scaleX), static_cast<float>(mouseY*scaleY));
	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
}

void CMain::GameLoop()
{
	while(running && csdl_setup->GetEvent()->type != SDL_QUIT)
	{
		frameStart = SDL_GetTicks();
		csdl_setup->Begin();

		SDL_Renderer* renderer = csdl_setup->GetRenderer();
		SDL_Window* window = csdl_setup->GetWindow();

		ImGui::NewFrame();
		UpdateImgui(csdl_setup);

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