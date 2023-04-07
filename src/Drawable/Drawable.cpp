#include "Drawable.h"

void Drawable::update(SDL_Renderer* rend) {

	SDL_RenderCopy(rend, tex, NULL, &rect);
}

int Drawable::getHeight()
{
	return rect.h;
}
int Drawable::getWidth()
{
	return rect.w;
}
int Drawable::getPosX()
{
	return rect.x;
}
int Drawable::getPosY()
{
	return rect.y;
}

void Drawable::setHeight(const int Height)
{
	rect.h = Height;
}
void Drawable::setWidth(const int Width)
{
	rect.w = Width;
}
void Drawable::setPosX(int x)
{
	rect.x = x;
}
void Drawable::setPosY(int y)
{
	rect.y = y;
}