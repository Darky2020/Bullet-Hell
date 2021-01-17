#include "Sound.h"

Sound::Sound(std::string FilePath)
{
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	song = Mix_LoadMUS(FilePath.c_str());
}

Sound::~Sound()
{
	Mix_FreeMusic(song);
}

void Sound::PlaySong()
{
	Mix_VolumeMusic(32); // 0-128
	Mix_PlayMusic(song, 1);
}

void Sound::Offset(float seconds)
{
	Mix_SetMusicPosition(seconds);
}

void Sound::Pause()
{
	Mix_PauseMusic();
}

void Sound::Resume()
{
	Mix_ResumeMusic();
}