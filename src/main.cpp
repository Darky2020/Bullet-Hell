#include "main.h"
#include "MainClass.h"

int main(int argc, char const *argv[])
{
	CMain* cmain = new CMain();
	cmain->GameLoop();
	atexit(SDL_Quit);
	return 0;
}