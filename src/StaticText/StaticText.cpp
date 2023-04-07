#include "StaticText.h"





StaticText::StaticText(Renderer* rend, const char* _text)
{
	tex = Renderer::loadFont(rend, _text);
	SDL_RenderCopy(rend->GetRenderer(), tex, &rect, NULL);

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

	rend->getDrawables()->push_back(this);

	//TODO ERROR HANDLING
}

StaticText::~StaticText()
{
	SDL_DestroyTexture(tex);
}
