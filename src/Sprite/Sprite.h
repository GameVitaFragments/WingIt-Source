#pragma once
#include "../Renderer/Renderer.h"
#include "../Collider/Collider.h"

class Player;


class Sprite:
	public Drawable
{

public:
	Sprite(Renderer*,const char*,bool);
	Sprite(Renderer*, const SDL_Color Color);
	~Sprite();

	virtual void update(SDL_Renderer* rend);
	Collider* getCol();
	virtual void isCollided(Player*);
	virtual void Destroy();
private:
	bool CollisionDet = false;
	Collider* col;
};

