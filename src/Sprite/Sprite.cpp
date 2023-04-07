#include "Sprite.h"



Sprite::Sprite(Renderer* rend,const char* path)
{
	tex = Renderer::loadTex(rend,path);
	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);

	rend->getDrawables()->push_back(this);
	
	//TODO ERROR HANDLING
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(tex);
}