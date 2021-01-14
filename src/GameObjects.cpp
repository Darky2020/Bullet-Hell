#include "GameObjects.h"
#include "SDL_DrawCircle.h"

GameObjects::GameObjects(SDL_Renderer* renderer, SDL_Event* event) {

	player = new Player(renderer, event, 400, 600);
	gameStats = new GameHud(renderer);
	Renderer = renderer;

	levelStarted = false;
	LevelStartedAt = 0;
}

GameObjects::~GameObjects() {

}

void GameObjects::UpdatePatterns() {
	std::vector<Pattern*>::iterator PatternIterator;
	int index = 0;

	for(PatternIterator = Patterns.begin(); PatternIterator != Patterns.end();)
	{
		Patterns[index]->UpdatePattern(player, Renderer, LevelStartedAt); 
		if(Patterns[index]->CanDeletePattern())
		{
			delete Patterns[index];
			Patterns[index] = NULL;
			PatternIterator = Patterns.erase(PatternIterator); 
		}
		else
		{
			++PatternIterator;
	 		index++;
		}
	}
}

Pattern* GameObjects::GetPatternByID(int id) {
	std::vector<Pattern*>::iterator PatternIterator;
	int index = 0;

	for(PatternIterator = Patterns.begin(); PatternIterator != Patterns.end();)
	{
		if(Patterns[index]->GetID() == id)
		{
			return Patterns[index];
		}
		else
		{
			++PatternIterator;
	 		index++;
		}
	}

	return NULL;
}

void GameObjects::UpdateTriggers() {
	std::vector<Trigger*>::iterator TriggerIterator;
	int index = 0;

	for(TriggerIterator = Triggers.begin(); TriggerIterator != Triggers.end();)
	{
		if(Triggers[index]->CheckIfCanBeExecuted(LevelStartedAt))
		{
			GetPatternByID(Triggers[index]->GetTargetID())->ChangePattern(
				Triggers[index]->GetChangeX(),
				Triggers[index]->GetChangeY(),
				Triggers[index]->GetChangeStep(),
				Triggers[index]->GetChangeAngle(),
				Triggers[index]->GetChangeVelocity(), 
				Triggers[index]->GetChangeRate(),
				Triggers[index]->GetChangeAcceleration(),
				Triggers[index]->GetChangeRays(),
				Triggers[index]->GetChangeSpread());

			delete Triggers[index];
			Triggers[index] = NULL;
			TriggerIterator = Triggers.erase(TriggerIterator); 
		}
		else
		{
			++TriggerIterator;
	 		index++;
		}
	}
}

void GameObjects::AddPattern(Pattern* pattern) {
	Patterns.push_back(pattern);
}

void GameObjects::AddTrigger(Trigger* trigger) {
	Triggers.push_back(trigger);
}

void GameObjects::DrawPlayerHitbox() {
	int x = (int)player->returnPlayerCenterX();
	int y = (int)player->returnPlayerCenterY();

	SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 0);
	SDL_RenderFillCircle(Renderer, x, y, 5);
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
}

void GameObjects::UpdateGameObjects() {
	if(!levelStarted) return;
	UpdatePatterns();
	UpdateTriggers();

	player->UpdatePlayer();
	DrawPlayerHitbox();
	
	gameStats->DrawBG();
	gameStats->DrawHearts(player->returnPlayerHealth());
}

void GameObjects::LoadLevel() {
	Patterns.clear();
	Triggers.clear();

	LevelStartedAt = SDL_GetTicks();
	levelStarted = true;

	AddPattern(new Pattern(0, HEIGHT/2, HEIGHT/2, 0, 5, 100, 0, 5, 1, 0, 5, 360));
	AddTrigger(new Trigger(5000, 0, None, None, None, None, None, None, -0.1, None, None));
	AddTrigger(new Trigger(10000, 0, None, None, None, None, 2, None, 0, None, None));
}
