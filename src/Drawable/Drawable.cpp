#include "Drawable.h"



void Drawable::update(SDL_Renderer* rend) {
	
	if(tex != nullptr)
		SDL_RenderCopyEx(rend, tex, NULL, &rect,angle,&centre,SDL_FLIP_NONE);
}

int Drawable::getHeight() const
{
	return rect.h;
}
int Drawable::getWidth() const
{
	return rect.w;
}
int Drawable::getPosX() const
{
	return rect.x;
}
int Drawable::getPosY() const
{
	return rect.y;
}

SDL_Point Drawable::getCentre() const
{
	return centre;
}

double Drawable::getAngle() const
{
	return angle;
}

void Drawable::setPos(const Vec2 _pos)
{
	setPosX(_pos.x);
	setPosY(_pos.y);
}

void Drawable::setSize(const Vec2 _scale)
{
	setWidth(_scale.x);
	setHeight(_scale.y);
}


void Drawable::setHeight(const int Height)
{
	rect.h = Height;
	reCentre();
}
void Drawable::setWidth(const int Width)
{
	rect.w = Width;
	reCentre();
}
void Drawable::setPosX(int x)
{
	rect.x = x;
	reCentre();
}
void Drawable::setPosY(int y)
{
	rect.y = y;
	reCentre();
}



void Drawable::reCentre()
{
	centre = { getWidth() / 2, getHeight() / 2 };
}

void Drawable::setCentre(int _x, int _y)
{
	centre = { _x, _y };
}

void Drawable::setAngle(double _angle)
{
	angle = _angle;
}

void Drawable::Destroy()
{
	tex = nullptr;
}
