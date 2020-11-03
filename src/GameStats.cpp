#include "GameStats.h"

GameStats::GameStats(SDL_Renderer* Renderer) {
	renderer = Renderer;

	heart1 = new CSprite(renderer, "packages/icons/heart_icon.png", HEIGHT+20, 10, 48, 48, 0);
	heart2 = new CSprite(renderer, "packages/icons/heart_icon.png", HEIGHT+70, 10, 48, 48, 0);
	heart3 = new CSprite(renderer, "packages/icons/heart_icon.png", HEIGHT+120, 10, 48, 48, 0);
}

void GameStats::DrawBG() {
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

void GameStats::DrawHearts(int health)
{
	// I really dont like this part, I wanna make a vector of hearts
	if(health > 0) heart1->Draw();
	if(health > 1) heart2->Draw();
	if(health > 2) heart3->Draw();
}