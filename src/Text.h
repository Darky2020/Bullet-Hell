#pragma once
#include "main.h"
class CText
{
public:
    CText(SDL_Renderer* passed_renderer, int x, int y, int size, uint8_t r, uint8_t g, uint8_t b, std::string TextToDisplay);
    ~CText();
 
    void Draw();
    void ChangeColor(uint8_t r, uint8_t g, uint8_t b);
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