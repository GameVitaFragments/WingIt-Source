#pragma once
#include <../src/Drawable/Drawable.h>
#include"../Error/Error.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include "../Collider/Collider.h"
#include <vector>
#include <unordered_map>
#include <string>

class Global {
public:
	static int wallWidth;
	static int ScreenWidth;
	static int ScreenHeight;
};


class Renderer
{

public:
	Renderer(SDL_Window*, Uint32);
	~Renderer();
	//void killRenderer();
	void update();
	SDL_Renderer* GetRenderer();
	std::vector<Drawable*>* getDrawables();
	static std::unordered_map<int, Collider*> cols;
	static std::unordered_map<int, Collider*>* getCols();
	void ClearScreen();
	static SDL_Texture* loadTex(Renderer*,const char*);
	static SDL_Texture* loadFont(Renderer* ,const char*,SDL_Color);
	static void drawFillRect(Renderer*, SDL_Color);

private:
	SDL_Renderer* rend;
	std::vector<Drawable*> drawables;
};

