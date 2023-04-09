#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../Error/Error.h"
#include <iostream>

class Audio {
public:
	Audio(const char* filename,bool isMusic);
	~Audio();
	//volume control
	void setVolume(int v);
	int getVolume();

	//play the audio
	int playMusic();
	int playSound();
	int attAudio(const char* filename, bool isMusic);
	int freeAudio();
	//run the following method once at the start and end of the program
	static int initMixer();	
	static int quitMixer();
	void togglePlay();
private:
	Mix_Music* music = nullptr;
	Mix_Chunk* sound = nullptr;
	int volume = (MIX_MAX_VOLUME * 80) / 100;
	int isMusic = false;
};