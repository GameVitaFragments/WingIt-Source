#pragma once
#include "../Renderer/Renderer.h"
#include "../Collider/Collider.h"


class Sprite:
	public Drawable
{

public:
	Sprite(Renderer*,const char*,bool);
	Sprite(Renderer*, const SDL_Color Color);
	~Sprite();

	virtual void update(SDL_Renderer* rend);
	Collider* getCol();
	void isCollided();
	virtual void Destroy();
private:
	bool CollisionDet = false;
	Collider* col;
};

