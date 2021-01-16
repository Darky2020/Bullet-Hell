#include "Text.h"
 
CText::CText(SDL_Renderer* passed_renderer, int x, int y, int size, uint8_t r, uint8_t g, uint8_t b, std::string TextToDisplay)
{
    renderer = passed_renderer;
    font = TTF_OpenFont("packages/fonts/font.ttf", size);
    if(font == NULL) printf("%s\n", "Couldn't load the font!");
    color = { r, g, b };
    PosX = x;
    PosY = y;
    Text = TextToDisplay;
    surface = TTF_RenderText_Solid(font, Text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}
 
 
CText::~CText()
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}
 
void CText::Draw()
{
    if(surface != NULL) SDL_FreeSurface(surface);
    surface = TTF_RenderText_Solid(font, Text.c_str(), color);
    if(texture != NULL) SDL_DestroyTexture(texture);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 0;

    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { PosX, PosY, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void CText::ChangeColor(uint8_t r, uint8_t g, uint8_t b)
{
    color = { r, g, b };
}

void CText::ChangeText(std::string TextToDisplay)
{
    Text = TextToDisplay;
}