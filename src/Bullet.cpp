#include "Bullet.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Player.h"

Bullet::Bullet(Player* Player, SDL_Renderer* renderer, float X, float Y, float ang, float vel, float accel)
{
	sourceX = X;
	sourceY = Y;
	angle = ang;
	velocity = vel;

	width = 6;
	height = 16;

	sprite = new CSprite(renderer, "packages/icons/proj1.png", sourceX, sourceY, width, height, angle);

	player = Player;

	acceleration = accel;
}

Bullet::~Bullet() 
{
	delete sprite;
	sprite = NULL;
}

auto Bullet::calculate_distance (float centerX, float centerY, float angle, float velocity) {
	// make so that 0 degrees points upwards

	angle *= -1;
	angle += 90;
	angle = M_PI * angle / 180 ;


	float x = centerX + velocity * cos(angle);
	float y = centerY - velocity * sin(angle);

	struct Position { 
	    float X, Y;
  	};

	return Position {x, y};
}

void Bullet::DrawBullet()
{
	sprite->SetX(sourceX);
	sprite->SetY(sourceY);
	sprite->SetRotation(angle);
	sprite->Draw();
}

void Bullet::MoveBullet()
{
	velocity += acceleration;
	auto [x, y] = calculate_distance(sourceX, sourceY, angle, velocity);

	sourceX = x;
	sourceY = y;
}

void Bullet::UpdateBullet()
{
	DrawBullet();
	MoveBullet();
	float x1 = (float)player->returnPlayerCenterX()-5;
	float y1 = (float)player->returnPlayerCenterY()-5;
	float x2 = (float)player->returnPlayerCenterX()+5;
	float y2 = (float)player->returnPlayerCenterY()-5;
	float x3 = (float)player->returnPlayerCenterX()+5;
	float y3 = (float)player->returnPlayerCenterY()+5;
	float x4 = (float)player->returnPlayerCenterX()-5;
	float y4 = (float)player->returnPlayerCenterY()+5;

	float centerX = sourceX + width/2;
	float centerY = sourceY + height/2;


	if(CheckIfCollidedWithPlayer((float)player->returnPlayerCenterX(), (float)player->returnPlayerCenterY(), 2, centerX, centerY, width, height) && !player->CheckIfInvulnerable())
	{
		player->GotHit();
	}
}

bool Bullet::CheckIfOutOfBounds()
{
	return (sourceX > (HEIGHT+100) || sourceX < -100 || sourceY > (HEIGHT+100) || sourceY < -100);
}

bool Bullet::CheckIfCollidedWithPlayer(float circleX, float circleY, float circleR, float centerX, float centerY, float rectW, float rectH)
{
	double unrotatedCircleX = cos(angle) * (circleX - centerX) - sin(angle) * (circleY - centerY) + centerX;
	double unrotatedCircleY  = sin(angle) * (circleX - centerX) + cos(angle) * (circleY - centerY) + centerY;
	 
	double closestX, closestY;
	 
	if (unrotatedCircleX  < sourceX)
	    closestX = sourceX;
	else if (unrotatedCircleX  > sourceX + rectW)
	    closestX = sourceX + rectW;
	else
	    closestX = unrotatedCircleX ;
	 
	if (unrotatedCircleY < sourceY)
	    closestY = sourceY;
	else if (unrotatedCircleY > sourceY + rectH)
	    closestY = sourceY + rectH;
	else
	    closestY = unrotatedCircleY;

	double a = abs(unrotatedCircleX - closestX);
    double b = abs(unrotatedCircleY - closestY);
 
    double distance = ceil((a * a) + (b * b));
	 
	if (distance < circleR*circleR)
	    return true;
	else
	    return false;
}