#include "Player.h"
#include <cmath>
#include <iostream>

Player::Player(Renderer* rend, const char* path, bool _collisionDet, EventHandler* event, int x, int y, int size, float gravity) : Sprite(rend, path, _collisionDet)
{
	this->event = event;
	this->vel = { 0, 0 };
	this->acc = { 0, 0 };
	this->dt = 0;
	this->gravity = gravity;
	gunBlastForce = 2;
	setPos({ x, y });
	setSize({ size, size });
}

void Player::checkCollision(Renderer* _rend)
{
	//Player Collider
	Collider* _playerCol = this->getCol();
	if (_playerCol == nullptr) {
		return;
	}
	vec::Vec2 PlayerPos = { this->getPosX(), this->getPosY() };
	vec::Vec2 PlayerBound = _playerCol->getBoundBox();
	for (auto col : *_rend->getCols()) {
		if (col.second == nullptr)
			continue;
		bool colX = false, colY = false;

		if (_playerCol == col.second) {
			continue;
		}
		vec::Vec2 ColPos = { col.second->getSprite()->getPosX(), col.second->getSprite()->getPosY() };
		vec::Vec2 ColBound = col.second->getBoundBox();

		//X Detection
		if (!(PlayerBound.x < ColPos.x || ColBound.x < PlayerPos.x)) {
			colX = true;
		}
		if (!(PlayerBound.y < ColPos.y || ColBound.y < PlayerPos.y)) {
			colY = true;
		}
		if (colX && colY) {
			col.second->getSprite()->isCollided();
		}
	}
}

void Player::getDt(double dt) {
	this->dt = dt;
}

void Player::update(SDL_Renderer* rend) {
	Sprite::update(rend);
	this->acc.y = gravity;
	if (event == nullptr) {
		return;
	}

	int mx = event->getPos('x');
	int my = event->getPos('y');
	float angle = atan2(my - getPosY(), mx - getPosX());

	reCentre();
	setAngle((int)(180 * angle / M_PI));


	//std::cout << cos(angle) << ", " << -sin(angle) << std::endl;
	if (event->getMSInput('1') && (SDL_GetTicks() - timeSinceShot > 1000)) {
		timeSinceShot = SDL_GetTicks();
		//angle += M_PI;
		this->vel.x = gunBlastForce * -cos(angle);
		this->vel.y = gunBlastForce * -sin(angle);
	}

	this->vel.x += this->acc.x * this->dt / 1000.0;
	this->vel.y += this->acc.y * this->dt / 1000.0;

	setPosX(getPosX() + (this->vel.x));
	setPosY(getPosY() + (this->vel.y));
	getCol()->setBoundBox();
}