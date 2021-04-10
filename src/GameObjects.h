#pragma once
#include "Pattern.h"
#include "Player.h"
#include "main.h"
#include "GameHud.h"
#include "Trigger.h"
#include "Sound.h"
#include "SDL_Setup.h"

class GameObjects
{
public:
	GameObjects(SDL_Renderer* renderer, SDL_Event* event);
	~GameObjects();

	void UpdatePatterns();
	Pattern* GetPatternByID(int id);

	void UpdateTriggers();

	void AddPattern(Pattern* pattern);
	void AddTrigger(Trigger* trigger);

	void DrawPlayerHitbox();

	void UpdateGameObjects(CSDL_Setup* csdl_setup, int *MenuState);

	void LoadLevel(std::string levelName);

	void Pause();
	void Resume();
	void Exit();

	void PauseMenu(int *MenuState);

	std::vector<Pattern*> Patterns;
	std::vector<Trigger*> Triggers;

	bool levelStarted;
	int LevelStartedAt;

	bool paused;
	int PausedAt, ResumedAt;

	int NumberOfBullets;

	const Uint8 *state;

private:
	Player* player;
	SDL_Renderer* Renderer;
	GameHud* gameHud;
	Sound* song;
	
};