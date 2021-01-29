#include "Pattern.h"
#include "Player.h"
#include "main.h"
#include "GameHud.h"
#include "Trigger.h"
#include "Sound.h"

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

	void UpdateGameObjects();

	void LoadLevel(std::string levelName);

	void Pause();
	void Resume();

	std::vector<Pattern*> Patterns;
	std::vector<Trigger*> Triggers;

	bool levelStarted;
	int LevelStartedAt;

	bool paused;
	int PausedAt;

	const Uint8 *state;

private:
	Player* player;
	SDL_Renderer* Renderer;
	GameHud* gameStats;
	Sound* song;
	
};