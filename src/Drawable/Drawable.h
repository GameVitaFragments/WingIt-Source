#pragma once
#include <SDL2/SDL.h> 

class Drawable
{
public:
	virtual void update(SDL_Renderer*);
	virtual int getWidth();
	virtual int getHeight();
	virtual int getPosX();
	virtual int getPosY();
	virtual void setWidth(const int);
	virtual void setHeight(const int);
	virtual void setPosX(int);
	virtual void setPosY(int);

protected:
	SDL_Texture* tex;
	SDL_Rect rect;
};

