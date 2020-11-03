#pragma once

#include "include/SDL.h"
#include "include/SDL_image.h"
#include "include/SDL_mixer.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>

#define HEIGHT_DEFAULT 720
#define WIDTH_DEFAULT 1280

#define HEIGHT 900
#define WIDTH 1600

#define HEIGHT_MULTIPLIER (float)HEIGHT/(float)HEIGHT_DEFAULT
#define WIDTH_MULTIPLIER (float)WIDTH/(float)WIDTH_DEFAULT
// g++ Sprite.cpp SDL_Setup.cpp main.cpp Main.cpp Bullet.cpp Pattern.cpp Player.cpp -lSDL2 -lSDL2_image
