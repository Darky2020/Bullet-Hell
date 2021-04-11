#include "Menus.h"
#include "Fonts.h"

Menus::Menus()
{
	
}

Menus::~Menus()
{
	
}

void Menus::DrawMainMenu(bool *running, int *MenuState, GameObjects *gameObjects)
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
	ImGui::Begin("MainMenu", NULL, window_flags);
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(1280, 720));
	ImGui::SetCursorPos(ImVec2(460, 100));
	ImGui::PushFont(Fonts[MAIN_MENU_TITLE_FONT]);
	ImGui::Text("Bullet hell");
	ImGui::PopFont();
	ImGui::PushFont(Fonts[DEFAULT_FONT]);
	ImGui::SetCursorPos(ImVec2(540, 200));
	if (ImGui::Button("Play", ImVec2(200, 80)))
	{
		gameObjects->LoadLevel("Test");
		*MenuState = MENUSTATE_INGAME;
	}
	ImGui::SetCursorPos(ImVec2(540, 320));
	if (ImGui::Button("Edit", ImVec2(200, 80)))
	{
		// Doesn't do anything yet.
	}
	ImGui::SetCursorPos(ImVec2(540, 440));
	if (ImGui::Button("Options", ImVec2(200, 80)))
	{
		// Doesn't do anything yet.
	}
	ImGui::SetCursorPos(ImVec2(540, 560));
	if (ImGui::Button("Quit", ImVec2(200, 80)))
	{
		*running = false;
	}
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void Menus::Update(bool *running, int *MenuState, GameObjects *gameObjects)
{
	DrawMainMenu(running, MenuState, gameObjects);
}