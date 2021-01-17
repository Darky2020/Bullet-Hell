#include "GameObjects.h"
#include "SDL_DrawCircle.h"

GameObjects::GameObjects(SDL_Renderer* renderer, SDL_Event* event) {

	player = new Player(renderer, event, 400, 600);
	gameStats = new GameHud(renderer);
	Renderer = renderer;
	song = NULL;
	levelStarted = false;
	LevelStartedAt = 0;
}

GameObjects::~GameObjects() {
	delete player;
	player = NULL;
	delete gameStats;
	gameStats = NULL;
	delete song;
	song = NULL;
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

void GameObjects::LoadLevel(std::string levelName) {
	Patterns.clear();
	Triggers.clear();

	LevelStartedAt = SDL_GetTicks();
	levelStarted = true;

	if(song != NULL)
	{
		delete song;
		song = NULL;
	}

	std::ifstream leveldata(levelName);
	std::string line;
	while (std::getline(leveldata, line)) {
    	if(line.find("Pattern") != std::string::npos)
    	{
    		unsigned first = line.find("{") + 1;
			unsigned last = line.find("}");
			std::string actualdata = line.substr(first, last-first);

			std::vector<char*> arguments;

			char *token = strtok(strdup(actualdata.c_str()), ", ");

			while (token != NULL)
		    {
		    	arguments.push_back(token);
		        token = strtok(NULL, ", ");
		    }

			AddPattern(new Pattern(std::stoi(arguments[0]), std::stof(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3]), std::stof(arguments[4]), std::stof(arguments[5]), std::stof(arguments[6]), std::stof(arguments[7]), std::stoi(arguments[8]), std::stof(arguments[9]), std::stoi(arguments[10]), std::stof(arguments[11]), std::stoi(arguments[12])));
    	}
    	if(line.find("Trigger") != std::string::npos)
    	{
    		unsigned first = line.find("{") + 1;
			unsigned last = line.find("}");
			std::string actualdata = line.substr(first, last-first);

			std::vector<char*> arguments;

			char *token = strtok(strdup(actualdata.c_str()), ", ");

			while (token != NULL)
		    {
		    	if(strcmp(token, "None") == 0) token = (char*)"-9999999";
		    	arguments.push_back(token);
		        token = strtok(NULL, ", ");
		    }

			AddTrigger(new Trigger(std::stoi(arguments[0]), std::stoi(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3]), std::stof(arguments[4]), std::stof(arguments[5]), std::stof(arguments[6]), std::stoi(arguments[7]), std::stof(arguments[8]), std::stoi(arguments[9]), std::stof(arguments[10])));
    	}
    	if(line.find("Song") != std::string::npos)
    	{
    		unsigned first = line.find("{") + 1;
			unsigned last = line.find("}");
			std::string actualdata = line.substr(first, last-first);

			std::vector<char*> arguments;

			char *token = strtok(strdup(actualdata.c_str()), ", ");

			while (token != NULL)
		    {
		    	arguments.push_back(token);
		        token = strtok(NULL, ", ");
		    }
		    song = new Sound(arguments[0]);
		    song->PlaySong();
		    song->Offset(std::stof(arguments[1]));
    	}
  	}
}
