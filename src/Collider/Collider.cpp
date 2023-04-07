#include "Collider.h"
#include "../Sprite/Sprite.h"
Collider::Collider(Sprite* _sp):
	boundBox({0,0}),sp(_sp)
{
	boundBox.x = sp->getPosX() + sp->getWidth();
	boundBox.y = sp->getPosY() + sp->getHeight();

}

Collider::~Collider()
{
}
void Collider::setBoundBox() 
{
	boundBox.x = sp->getWidth();
	boundBox.y = sp->getHeight();
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
