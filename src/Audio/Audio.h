#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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
	//run the following method once at the start and end of the program
	int initMixer();	
	int quitMixer();
	void togglePlay();
private:
	Mix_Music* music;
	Mix_Chunk* sound;
	int volume;
};