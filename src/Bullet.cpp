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

	width = 6*WIDTH_MULTIPLIER;
	height = 16*HEIGHT_MULTIPLIER;

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
	float x1 = (float)player->returnPlayerCenterX()-(1*HEIGHT_MULTIPLIER);
	float y1 = (float)player->returnPlayerCenterY()-(1*HEIGHT_MULTIPLIER);
	float x2 = (float)player->returnPlayerCenterX()+(1*HEIGHT_MULTIPLIER);
	float y2 = (float)player->returnPlayerCenterY()-(1*HEIGHT_MULTIPLIER);
	float x3 = (float)player->returnPlayerCenterX()+(1*HEIGHT_MULTIPLIER);
	float y3 = (float)player->returnPlayerCenterY()+(1*HEIGHT_MULTIPLIER);
	float x4 = (float)player->returnPlayerCenterX()-(1*HEIGHT_MULTIPLIER);
	float y4 = (float)player->returnPlayerCenterY()+(1*HEIGHT_MULTIPLIER);
	if(CheckIfCollidedWithPlayer(x1, y1, x2, y2, x3, y3, x4, y4) && !player->CheckIfInvulnerable())
	{
		player->GotHit();
	}
}

bool Bullet::CheckIfOutOfBounds()
{
	return (sourceX > (HEIGHT+100)*HEIGHT_MULTIPLIER || sourceX < -100*HEIGHT_MULTIPLIER || sourceY > (HEIGHT+100)*HEIGHT_MULTIPLIER || sourceY < -100*HEIGHT_MULTIPLIER);
}

bool Bullet::CheckIfCollidedWithPlayer(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{	
	// Top_Right
	float Bx = sourceX + ((width / 2) * cos(angle)) - ((height / 2) * sin(angle));
	float By = sourceY + ((width / 2) * sin(angle)) + ((height / 2) * cos(angle));
	// Top_Left
	float Ax = sourceX - ((width / 2) * cos(angle)) - ((height / 2) * sin(angle));
	float Ay = sourceY - ((width / 2) * sin(angle)) + ((height / 2) * cos(angle));
	// Bot_Left
	float Dx = sourceX - ((width / 2) * cos(angle)) + ((height / 2) * sin(angle));
	float Dy = sourceY - ((width / 2) * sin(angle)) - ((height / 2) * cos(angle));

	float Mx = x1;
	float My = y1;

	float AM = sqrt( (Mx-Ax)*(Mx-Ax) + (My-Ay)*(My-Ay) );
	float AB = sqrt( (Bx-Ax)*(Bx-Ax) + (By-Ay)*(By-Ay) );
	float AD = sqrt( (Dx-Ax)*(Dx-Ax) + (Dy-Ay)*(Dy-Ay) );

	if(AM*AB > 0 && AB*AB > AM*AB && AM*AD > 0 && AD*AD > AM*AD) return true;

	Mx = x2;
	My = y2;

	AM = sqrt( (Mx-Ax)*(Mx-Ax) + (My-Ay)*(My-Ay) );
	AB = sqrt( (Bx-Ax)*(Bx-Ax) + (By-Ay)*(By-Ay) );
	AD = sqrt( (Dx-Ax)*(Dx-Ax) + (Dy-Ay)*(Dy-Ay) );

	if(AM*AB > 0 && AB*AB > AM*AB && AM*AD > 0 && AD*AD > AM*AD) return true;

	Mx = x3;
	My = y3;

	AM = sqrt( (Mx-Ax)*(Mx-Ax) + (My-Ay)*(My-Ay) );
	AB = sqrt( (Bx-Ax)*(Bx-Ax) + (By-Ay)*(By-Ay) );
	AD = sqrt( (Dx-Ax)*(Dx-Ax) + (Dy-Ay)*(Dy-Ay) );

	if(AM*AB > 0 && AB*AB > AM*AB && AM*AD > 0 && AD*AD > AM*AD) return true;

	Mx = x4;
	My = y4;

	AM = sqrt( (Mx-Ax)*(Mx-Ax) + (My-Ay)*(My-Ay) );
	AB = sqrt( (Bx-Ax)*(Bx-Ax) + (By-Ay)*(By-Ay) );
	AD = sqrt( (Dx-Ax)*(Dx-Ax) + (Dy-Ay)*(Dy-Ay) );

	if(AM*AB > 0 && AB*AB > AM*AB && AM*AD > 0 && AD*AD > AM*AD) return true;

	return false;

}