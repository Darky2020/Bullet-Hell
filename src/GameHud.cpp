#include "GameHud.h"

GameHud::GameHud(SDL_Renderer* Renderer) {
	renderer = Renderer;

	HealthText = new CText(renderer, HEIGHT+20, 10, 30, 255, 255, 255, "Health: ");
}

GameHud::~GameHud() {
	delete HealthText;
	HealthText = NULL;
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

void GameHud::DrawHearts(int health) {
	HealthText->ChangeText("Health : " + std::to_string(health));
	HealthText->Draw();
}