#include "main.h"

class Sound
{
public:
	Sound(std::string FilePath);
	~Sound();

	void PlaySong();
	void Offset(float seconds);
	void Pause();
	void Resume();

	Mix_Music *song;
	
};