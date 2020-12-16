#include "Player.h"

Player::Player(SDL_Renderer* renderer, SDL_Event* event, int x, int y)
{
	PosX = x;
	PosY = y;

	Event = event;

	PlayerSpriteWidth = 20*1.5;
	PlayerSpriteHeight = 24*1.5;
	sprite = new CSprite(renderer, "packages/icons/player.png", PosX, PosY, PlayerSpriteWidth, PlayerSpriteHeight, 0);;

	speed = 6;

	state = SDL_GetKeyboardState(NULL);

	centerX = 0;
	centerY = 0;

	HitAtTime = 0;

	isInvulnerable = false;

	health = 3;
}

void Player::DrawPlayer()
{
	sprite->SetX(PosX);
	sprite->SetY(PosY);
	if((SDL_GetTicks()%500<250 && isInvulnerable) || !isInvulnerable)
	{
	sprite->Draw();
	}
}

void Player::Move()
{
    if(state[SDL_SCANCODE_LSHIFT])
    {
    
	    if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) { if(PosY-((speed/4)*1.5) >= 0) {PosY -= (speed/4)*1.5;} if(PosX+(speed/4)*1.5 <= HEIGHT-PlayerSpriteWidth) {PosX += (speed/4)*1.5;  }}
	    else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) { if(PosY-((speed/4)*1.5) >= 0) {PosY -= (speed/4)*1.5;} if(PosX-(speed/4)*1.5 >= 0) {PosX -= (speed/4)*1.5;}}
	    else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D]) { if(PosY+((speed/4)*1.5) <= HEIGHT-PlayerSpriteHeight) {PosY += (speed/4)*1.5;} if(PosX+(speed/4)*1.5 <= HEIGHT-PlayerSpriteWidth) {PosX += (speed/4)*1.5;}}
	    else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A]) { if(PosY+((speed/4)*1.5) <= HEIGHT-PlayerSpriteHeight) {PosY += (speed/4)*1.5;} if(PosX-(speed/4)*1.5 >= 0) {PosX -= (speed/4)*1.5;}}
	    else if (state[SDL_SCANCODE_W]) { if(PosY-(speed/2) >= 0) {PosY -= speed/2;}}
	    else if (state[SDL_SCANCODE_A]) { if(PosX-(speed/2) >= 0) {PosX -= speed/2;}}
	    else if (state[SDL_SCANCODE_S]) { if(PosY+(speed/2) <= HEIGHT-PlayerSpriteHeight) {PosY += speed/2;}}
	    else if (state[SDL_SCANCODE_D]) { if(PosX+(speed/2) <= HEIGHT-PlayerSpriteWidth) {PosX += speed/2;}}
    
    }
    else
	{
		if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) { if(PosY-((speed/2)*1.5) >= 0) {PosY -= (speed/2)*1.5;} if(PosX+(speed/2)*1.5 <= HEIGHT-PlayerSpriteWidth) {PosX += (speed/2)*1.5;  }}
	    else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) { if(PosY-((speed/2)*1.5) >= 0) {PosY -= (speed/2)*1.5;} if(PosX-(speed/2)*1.5 >= 0) {PosX -= (speed/2)*1.5;}}
	    else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D]) { if(PosY+((speed/2)*1.5) <= HEIGHT-PlayerSpriteHeight) {PosY += (speed/2)*1.5;} if(PosX+(speed/2)*1.5 <= HEIGHT-PlayerSpriteWidth) {PosX += (speed/2)*1.5;}}
	    else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A]) { if(PosY+((speed/2)*1.5) <= HEIGHT-PlayerSpriteHeight) {PosY += (speed/2)*1.5;} if(PosX-(speed/2)*1.5 >= 0) {PosX -= (speed/2)*1.5;}}
	    else if (state[SDL_SCANCODE_W]) { if(PosY-(speed) >= 0) {PosY -= speed;}}
	    else if (state[SDL_SCANCODE_A]) { if(PosX-(speed) >= 0) {PosX -= speed;}}
	    else if (state[SDL_SCANCODE_S]) { if(PosY+(speed) <= HEIGHT-PlayerSpriteHeight) {PosY += speed;}}
	    else if (state[SDL_SCANCODE_D]) { if(PosX+(speed) <= HEIGHT-PlayerSpriteWidth) {PosX += speed;}}
	}     
}

void Player::UpdatePlayer()
{
	centerX = PosX+(PlayerSpriteWidth)/2;
	centerY = PosY+(PlayerSpriteHeight)/2;

	if(HitAtTime+2000 > SDL_GetTicks() && HitAtTime > 0) isInvulnerable = true;
	else isInvulnerable = false;

	DrawPlayer();
	Move();
}

float Player::returnPlayerCenterX() { return centerX; }
float Player::returnPlayerCenterY() { return centerY; }
float Player::returnPlayerPosX() { return PosX; }
float Player::returnPlayerPosY() { return PosY; }

void Player::GotHit()
{
	isInvulnerable = true;
	HitAtTime = SDL_GetTicks();
	health -= 1;
}

bool Player::CheckIfInvulnerable()
{
	return isInvulnerable;
}