#pragma once

class Sprite;
namespace vec {
	struct Vec2
	{
		int x;
		int y;
	};
	struct Vec2f
	{
		float x;
		float y;
	};
}
class Collider
{
	
public:
	Collider(Sprite*);
	~Collider();
	void setBoundBox();
	void setBoundBox(vec::Vec2);
	void updateBoundBox(int, int);
	vec::Vec2 getBoundBox();
	int getID() const;
	Sprite* getSprite();
private:
	vec::Vec2 boundBox;
	Sprite* sp;
	static int _colcount;
	int _colID;
};
