#pragma once
#include <unordered_map>
#include "../Renderer/Renderer.h"
#include <string>

class StaticText:
	public Drawable
{
public:
	StaticText(Renderer*, const char*,SDL_Color);
	~StaticText();
	void CacheNumbers(Renderer*, SDL_Color);
	void RenderNumber(int);

private:
	std::unordered_map<int, SDL_Texture*> _numMap;

};

