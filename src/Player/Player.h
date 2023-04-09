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

public:
	Player(Renderer*, const char*, bool, EventHandler*, int, int, float, float);
	void checkCollision(Renderer*);
	void update(SDL_Renderer* rend);
	void getDt(double);
	int coolDown;
	bool underCooldown;
	int Hearts;
	Uint32 timeSinceShot;
};
