#pragma once
#include <../src/Drawable/Drawable.h>
#include"../Error/Error.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include <string>


class Renderer
{

public:
	Renderer(SDL_Window*, Uint32);
	~Renderer();
	void update();
	SDL_Renderer* GetRenderer();
	std::vector<Drawable*>* getDrawables();
	void ClearScreen();
	static SDL_Texture* loadTex(Renderer*,const char*);
	static SDL_Texture* loadFont(Renderer* ,const char*);
	static void drawFillRect(Renderer*, SDL_Color);

private:
	SDL_Renderer* rend;
	std::vector<Drawable*> drawables;
};

