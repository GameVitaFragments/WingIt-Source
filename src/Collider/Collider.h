#pragma once

class Sprite;
namespace vec {
	struct Vec2
	{
		int x;
		int y;
	};
}
class Collider
{
	
public:
	Collider(Sprite*);
	~Collider();
	void setBoundBox();
	void setBoundBox(vec::Vec2);
	vec::Vec2 getBoundBox();
private:
	vec::Vec2 boundBox;
	Sprite* sp;

};

