#pragma once
#include <SDL2/SDL_events.h>

class EventHandler
{
private:
	bool _m1 = false;
	bool _m2 = false;
	bool _m3 = false;
	int _x = 0;
	int _y = 0;
	bool _w = false;
	bool _a = false;
	bool _s = false;
	bool _d = false;
	bool _quit = false;
public:
	void setInput(SDL_Event*);
	bool getKBInput(char);
	bool getMSInput(char);
	int getPos(char);
	bool isQuit();
};