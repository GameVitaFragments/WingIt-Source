#pragma once
#include <../src/Drawable/Drawable.h>
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
	static SDL_Texture* loadTex(Renderer* rend,const char*);
	static SDL_Texture* loadFont(Renderer* ,const char*);

private:
	SDL_Renderer* rend;
	std::vector<Drawable*> drawables;
};

