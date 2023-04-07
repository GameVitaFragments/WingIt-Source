#include "Sprite.h"



Sprite::Sprite(Renderer* rend, const char* path,bool _collisionDet):
	col(nullptr)
{
	angle = 0;
	tex = Renderer::loadTex(rend,path);

	// connects our texture with dest to control position
	error::checkReturnCode(SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h));
	rend->getDrawables()->push_back(this);
	reCentre();
	//TODO ERROR HANDLING
	if (!_collisionDet)
		return;
	col = new Collider(this);
	rend->getCols()->insert(std::make_pair(col->getID(), col));
	CollisionDet = true;
}

void Sprite::update(SDL_Renderer* rend) 
{
	Drawable::update(rend);
	//printf("%d\n",CollisionDet);
	if (!CollisionDet)
		return;

	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_Rect n_rect = { rect.x, rect.y,col->getBoundBox().x-rect.x,col->getBoundBox().y-rect.y};
	error::checkReturnCode(SDL_RenderDrawRect(rend, &n_rect));
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	

}

Collider* Sprite::getCol()
{
	if (CollisionDet)
		return col;
	return nullptr;
}

void Sprite::isCollided()
{
	printf("Yay!!! Collided!!");
}

Sprite::Sprite(Renderer* rend, const SDL_Color Color)
{
	/*angle = 0;
	tex = Renderer::drawFillRect(rend, Color);

	// connects our texture with dest to control position
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	rend->getDrawables()->push_back(this);
	reCentre();*/
	//TODO ERROR HANDLING

}

Sprite::~Sprite()
{
	SDL_DestroyTexture(tex);
	if (CollisionDet)
		delete col;
}