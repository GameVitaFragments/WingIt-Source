#pragma once
#include "../Renderer/Renderer.h"

class StaticText:
	public Drawable
{
public:
	StaticText(Renderer*, const char*);
	~StaticText();

};

