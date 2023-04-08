#include "Collider.h"
#include "../Sprite/Sprite.h"

int Collider::_colcount = 0;

Collider::Collider(Sprite* _sp):
	boundBox({0,0}),sp(_sp)
{
	boundBox.x = sp->getPosX() + sp->getWidth();
	boundBox.y = sp->getPosY() + sp->getHeight();

	_colcount++;
	_colID = _colcount;
}

Collider::~Collider()
{
}
void Collider::setBoundBox() 
{
	if (this == nullptr) {
		return;
	}
	boundBox.x = sp->getPosX() + sp->getWidth();
	boundBox.y = sp->getPosY() + sp->getHeight();
	printf("%d", _colID);
}

void Collider::updateBoundBox(int oldx,int oldy)
{
	if (this == nullptr) {
		return;
	}
	boundBox.x = sp->getPosX() + boundBox.x - oldx;
	boundBox.y = sp->getPosY() + boundBox.y -oldy;
}

void Collider::setBoundBox(vec::Vec2 _size)
{
	if (this == nullptr) {
		return;
	}
	boundBox.x = _size.x;
	boundBox.y = _size.y;
}

vec::Vec2 Collider::getBoundBox()
{
	if (this == nullptr) {
		return { INT_MIN, INT_MAX };
	}
	return boundBox;
}

int Collider::getID() const
{
	if (this == nullptr) {
		return -1;
	}
	return _colID;
}

Sprite* Collider::getSprite()
{
	if (this == nullptr) {
		return nullptr;
	}
	return sp;
}


