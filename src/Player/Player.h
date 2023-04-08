#pragma once
#include "../Sprite/Sprite.h"
#include "../Event/EventHandler.h"

class Player : public Sprite
{
private:
	EventHandler* event;
	vec::Vec2f vel;
	vec::Vec2f acc;
	double dt;
	float gravity;
	float gunBlastForce;
	Uint32 timeSinceShot;

public:
	Player(Renderer*, const char*, bool, EventHandler*, int, int, int, float);
	void checkCollision(Renderer*);
	void update(SDL_Renderer* rend);
	void getDt(double);
};