#include "StaticText.h"

void StaticText::CacheNumbers(Renderer* rend, const SDL_Color color) 
{
	for (int i = 0; i < 10; i++)
	{
		_numMap[i] = Renderer::loadFont(rend, std::to_string(i).c_str(), color);
	}
}

void StaticText::RenderNumber(int num)
{
	tex = _numMap[num];
}


StaticText::StaticText(Renderer* rend, const char* _text,const SDL_Color color)
{
	tex = Renderer::loadFont(rend, _text, color);
	SDL_RenderCopy(rend->GetRenderer(), tex, &rect, NULL);

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	reCentre();
	rend->getDrawables()->push_back(this);

	//TODO ERROR HANDLING
}

StaticText::~StaticText()
{
	SDL_DestroyTexture(tex);
}
