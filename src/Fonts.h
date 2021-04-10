#pragma once
#include "main.h"

enum {
    DEFAULT_FONT = 0,
    PAUSE_MENU_TITLE_FONT,
    MAIN_MENU_TITLE_FONT,
};

static ImFont* CreateFont(const char* path, float size)
{
    ImGui::CreateContext();
    return ImGui::GetIO().Fonts->AddFontFromFileTTF(path, size);
}

static ImFont* Fonts[] =
{
    CreateFont("packages/fonts/font.ttf", 25.f),
    CreateFont("packages/fonts/font.ttf", 45.f),
    CreateFont("packages/fonts/font.ttf", 60.f),
};