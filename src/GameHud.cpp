#include "GameHud.h"

GameHud::GameHud(SDL_Renderer* Renderer) {
	renderer = Renderer;
}

GameHud::~GameHud() {

}

void GameHud::DrawBG() {
	SDL_Rect rect;

	// Draw a black rect outside of playfield to clear anything (like bullets) that could go out of bounds
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	rect.x = HEIGHT;
    rect.y = 0;
    rect.w = HEIGHT;
    rect.h = HEIGHT;
    SDL_RenderFillRect(renderer, &rect);

    // Draw white lines
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
}

void GameHud::DrawStats(int health, int NumberOfBullets) {

	// HealthText->ChangeText("Health : " + std::to_string(health));
	// HealthText->Draw();

	ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 1.f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 1.f));
	ImGui::Begin("Stats", NULL, window_flags);
	ImGui::SetWindowPos(ImVec2(740, 10));
	ImGui::SetWindowSize(ImVec2(700, 700));
	ImGui::SetCursorPos(ImVec2(10, 10));
	ImGui::Text("Health : %d", health);
	ImGui::Text("Bullets : %d", NumberOfBullets);
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

}

void GameHud::UpdateImgui(CSDL_Setup* csdl_setup) {
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