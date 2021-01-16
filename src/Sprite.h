#pragma once
#include "main.h"
class CSprite
{
public:
    CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, float angle);
    ~CSprite(void);
 
    void Draw();

    void SetX(int X);
    void SetY(int Y);
    void SetRotation(float ang);
    void SetPos(int X, int Y);
    int GetX();
    int GetY();
    float GetRotation();
 
private:
    SDL_Texture* image;
    SDL_Rect rect;

    float angle;
 
    SDL_Renderer* renderer;
};