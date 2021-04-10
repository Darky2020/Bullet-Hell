#include "GameObjects.h"
#include "SDL_DrawCircle.h"
#include "Fonts.h"

GameObjects::GameObjects(SDL_Renderer* renderer, SDL_Event* event) {

	player = new Player(renderer, event, 400, 600);
	gameHud = new GameHud(renderer);
	Renderer = renderer;
	song = NULL;
	levelStarted = false;
	LevelStartedAt = 0;
	PausedAt = 0;
	ResumedAt = 0;

	paused = false;

	NumberOfBullets = 0;

	state = SDL_GetKeyboardState(NULL);
}

GameObjects::~GameObjects() {
	delete player;
	player = NULL;
	delete gameHud;
	gameHud = NULL;
	delete song;
	song = NULL;
}

void GameObjects::UpdatePatterns() {
	NumberOfBullets = 0;
	std::vector<Pattern*>::iterator PatternIterator;
	int index = 0;

	for(PatternIterator = Patterns.begin(); PatternIterator != Patterns.end();)
	{
		NumberOfBullets += Patterns[index]->GetNumberOfBullets();

		Patterns[index]->UpdatePattern(player, Renderer, LevelStartedAt, paused); 
		if(Patterns[index]->CanDeletePattern(LevelStartedAt))
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
		if(Triggers[index]->CheckIfCanBeExecuted(LevelStartedAt) && !paused)
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
				Triggers[index]->GetChangeSpread(),
				Triggers[index]->GetChangeBulletLifeime());

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

void GameObjects::UpdateGameObjects(CSDL_Setup* csdl_setup, int *MenuState) {
	if (state[SDL_SCANCODE_Z] && SDL_GetTicks()-ResumedAt>1000 && !paused) { Pause(); }

	if(!levelStarted) return;

	UpdatePatterns();
	UpdateTriggers();

	player->UpdatePlayer(LevelStartedAt, paused);
	DrawPlayerHitbox();
	
	gameHud->DrawBG();
	gameHud->DrawStats(player->returnPlayerHealth(), NumberOfBullets);

	if(paused) PauseMenu(MenuState);
}

void GameObjects::LoadLevel(std::string levelName) {
	Patterns.clear();
	Triggers.clear();

	if(song != NULL)
	{
		delete song;
		song = NULL;
	}

	player->Reset();

	std::string current_level_dir("Levels/"+levelName+"/");

	std::ifstream leveldata(current_level_dir+"level.bhl");
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

			AddTrigger(new Trigger(std::stoi(arguments[0]), std::stoi(arguments[1]), std::stof(arguments[2]), std::stof(arguments[3]), std::stof(arguments[4]), std::stof(arguments[5]), std::stof(arguments[6]), std::stoi(arguments[7]), std::stof(arguments[8]), std::stoi(arguments[9]), std::stof(arguments[10]), std::stoi(arguments[11])));
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
		    song = new Sound(current_level_dir+arguments[0]);
		    song->PlaySong();
		    song->Offset(std::stof(arguments[1]));
    	}

    	LevelStartedAt = SDL_GetTicks(); // check this thingy
		levelStarted = true;
		paused = false;
  	}
}

void GameObjects::Pause()
{
	if(!paused)
	{
		paused = true;
		PausedAt = SDL_GetTicks();
		song->Pause();
	}
}

void GameObjects::Resume()
{
	if(paused)
	{
		int PauseDuration = SDL_GetTicks() - PausedAt;
		LevelStartedAt += PauseDuration;
		PausedAt = 0;
		ResumedAt = SDL_GetTicks();
		paused = false;
		song->Resume();
	}
}

void GameObjects::Exit()
{
	Patterns.clear();
	Triggers.clear();
	LevelStartedAt = 0;
	levelStarted = false;
	paused = false;

	if(song != NULL)
	{
		delete song;
		song = NULL;
	}
}

void GameObjects::PauseMenu(int *MenuState)
{
	ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.f, 0.f, 0.f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.0f));
	ImGui::Begin("PauseMenu", NULL, window_flags);
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(1280, 720));
	ImGui::SetCursorPos(ImVec2(575, 100));
	ImGui::PushFont(Fonts[PAUSE_MENU_TITLE_FONT]);
	ImGui::Text("Paused");
	ImGui::PopFont();
	ImGui::PushFont(Fonts[DEFAULT_FONT]);
	ImGui::SetCursorPos(ImVec2(540, 250));
	if (ImGui::Button("Resume", ImVec2(200, 80)))
	{
		Resume();
	}
	ImGui::SetCursorPos(ImVec2(540, 400));
	if (ImGui::Button("Retry", ImVec2(200, 80)))
	{
		LoadLevel("Test");
		Resume();
	}
	ImGui::SetCursorPos(ImVec2(540, 550));
	if (ImGui::Button("Quit", ImVec2(200, 80)))
	{
		Exit();
		*MenuState = MENUSTATE_MAINMENU;
	}
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}