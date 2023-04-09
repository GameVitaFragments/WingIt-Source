#pragma once
#include <SDL2/SDL.h> 

class Drawable
{
	struct Vec2
	{
		int x;
		int y;
	};
public:
	virtual void update(SDL_Renderer*);
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual int getPosX() const;
	virtual int getPosY() const;
	virtual SDL_Point getCentre() const;
	virtual double getAngle() const;
	virtual void setPos(const Vec2);
	virtual void setSize(const Vec2);
	virtual void setWidth(const int);
	virtual void setHeight(const int);
	virtual void setPosX(int);
	virtual void setPosY(int);
	virtual void reCentre();
	virtual void setCentre(int,int);
	virtual void setAngle(double);
	virtual void Destroy();

protected:
	SDL_Texture* tex;
	SDL_Rect rect;
	SDL_Point centre;
	double angle;
	bool facingLeft = false;

};

