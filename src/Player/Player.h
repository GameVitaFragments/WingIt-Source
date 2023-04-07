#pragma once
#include "../Sprite/Sprite.h"

class Player : public Sprite
{
public:
	Player(Renderer*, const char*, bool);

	void checkCollision(Renderer*);
};

