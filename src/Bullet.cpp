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
	float x1 = (float)player->returnPlayerCenterX()-2;
	float y1 = (float)player->returnPlayerCenterY()-2;
	float x2 = (float)player->returnPlayerCenterX()+2;
	float y2 = (float)player->returnPlayerCenterY()-2;
	float x3 = (float)player->returnPlayerCenterX()+2;
	float y3 = (float)player->returnPlayerCenterY()+2;
	float x4 = (float)player->returnPlayerCenterX()-2;
	float y4 = (float)player->returnPlayerCenterY()+2;
	if(CheckIfCollidedWithPlayer(x1, y1, x2, y2, x3, y3, x4, y4) && !player->CheckIfInvulnerable())
	{
		player->GotHit();
	}
}

bool Bullet::CheckIfOutOfBounds()
{
	return (sourceX > (HEIGHT+100) || sourceX < -100 || sourceY > (HEIGHT+100) || sourceY < -100);
}

bool Bullet::CheckIfCollidedWithPlayer(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{	

	float tempX1 = x1 - (sourceX+width/2);
	float tempY1 = y1 - (sourceY+height/2);

	float tempX2 = x2 - (sourceX+width/2);
	float tempY2 = y2 - (sourceY+height/2);

	float tempX3 = x3 - (sourceX+width/2); // actually not needed rn but might be in the future
	float tempY3 = y3 - (sourceY+height/2); // actually not needed rn but might be in the future

	float tempX4 = x4 - (sourceX+width/2);
	float tempY4 = y4 - (sourceY+height/2);

	float rotatedX1 = tempX1*cos(angle) - tempY1*sin(angle);
	float rotatedY1 = tempX1*sin(angle) + tempY1*cos(angle);

	float rotatedX2 = tempX2*cos(angle) - tempY2*sin(angle);
	float rotatedY2 = tempX2*sin(angle) + tempY2*cos(angle);

	float rotatedX3 = tempX3*cos(angle) - tempY3*sin(angle); // actually not needed rn but might be in the future
	float rotatedY3 = tempX3*sin(angle) + tempY3*cos(angle); // actually not needed rn but might be in the future

	float rotatedX4 = tempX4*cos(angle) - tempY4*sin(angle);
	float rotatedY4 = tempX4*sin(angle) + tempY4*cos(angle);

	// Top_Right
	float Bx = rotatedX2 + (sourceX+width/2);
	float By = rotatedY2 + (sourceY+height/2);

	// Top_Left
	float Ax = rotatedX1 + (sourceX+width/2);
	float Ay = rotatedY1 + (sourceY+height/2);

	// Bot_Left
	float Dx = rotatedX4 + (sourceX+width/2);
	float Dy = rotatedY4 + (sourceY+height/2);

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