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
	boundBox.x = sp->getPosX() + sp->getWidth();
	boundBox.y = sp->getPosY() + sp->getHeight();
}

void Collider::updateBoundBox(int oldx,int oldy)
{
	boundBox.x = sp->getPosX() + boundBox.x - oldx;
	boundBox.y = sp->getPosY() + boundBox.y -oldy;
}

void Collider::setBoundBox(vec::Vec2 _size)
{
	boundBox.x = _size.x;
	boundBox.y = _size.y;
}

vec::Vec2 Collider::getBoundBox()
{
	return boundBox;
}

int Collider::getID() const
{
	return _colID;
}

Sprite* Collider::getSprite()
{
	return sp;
}


