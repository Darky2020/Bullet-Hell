#pragma once
#include "main.h"
class CText
{
public:
        CText(SDL_Renderer* passed_renderer, int x, int y, int size, int r, int g, int b, std::string TextToDisplay);
        ~CText();
 
        void Draw();
        void ChangeColor(int r, int g, int b);
        void ChangeText(std::string TextToDisplay);
 
private:
        int PosX, PosY;
        std::string Text;
        TTF_Font* font;
        SDL_Color color;
        SDL_Renderer* renderer;
        SDL_Surface* surface;
        SDL_Texture* texture;
};