#include "Audio.h"

Audio::Audio(const char* filename, bool isMusic) {
	if (isMusic) {
		//Mix_Music* m = NULL;
		//m = Mix_LoadMUS(filename);
		//music = m;
		music = Mix_LoadMUS(filename);
	}
	else {
		//Mix_Chunk* m = NULL;
		//m = Mix_LoadWAV(filename);
		//sound = m;
		sound = Mix_LoadWAV(filename);
		//error handling
	}
}

Audio::~Audio() {
	Mix_FreeChunk(sound);
	Mix_FreeMusic	(music);
}

void Audio::setVolume(int v)
{
	volume = (MIX_MAX_VOLUME * v) / 100;
}

int Audio::getVolume()
{
	if (volume) {
		return (volume * 100) / MIX_MAX_VOLUME;
	}
	return 0;
}

int Audio::playMusic()
{
	if (Mix_PlayingMusic() == 0) {
		Mix_Volume(1, volume);
		Mix_PlayMusic(music, -1);
	}
	return 0;
}

int Audio::playSound()
{
	Mix_Volume(-1, volume);
	Mix_PlayChannel(-1, sound, 0);
	return 0;
}

int Audio::initMixer()
{
	Mix_Init(MIX_INIT_MP3);
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,2048) < 0) {
		printf("SDL_mixer couldn't init. Err: %s\n", Mix_GetError);
		return -1;
	}
	setVolume(80);
	return 0;
}

int Audio::quitMixer()
{
	Mix_FreeChunk(sound);
	Mix_FreeMusic(music);
	Mix_Quit();
	return 0;
}

void Audio::togglePlay()
{
	if (Mix_PausedMusic() == 1) {
		Mix_ResumeMusic();
	}
	else {
		Mix_PauseMusic();
	}
}
