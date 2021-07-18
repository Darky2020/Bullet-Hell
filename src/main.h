#pragma once

#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_mixer.h"
#include "include/SDL_ttf.h"

#include "include/imgui.h"
#include "include/imgui_sdl.h"

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include "include/stdc++.h"

#define HEIGHT 720
#define WIDTH 1280

#define None -9999999

enum {
	MENUSTATE_MAINMENU = 0,
	MENUSTATE_INGAME,
};