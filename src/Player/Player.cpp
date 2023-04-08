#include "Player.h"

Player::Player(Renderer* rend, const char* path, bool _collisionDet) : Sprite(rend, path, _collisionDet)
{
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
