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