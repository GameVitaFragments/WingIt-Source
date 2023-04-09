#include "Game.h"
#include <iostream>
#include <vector>



class RougeRock :
	public Sprite
{
private:
	vec::Vec2f _velocity;
	vec::Vec2 _position;
	vec::Vec2f _positionF;
	float _gravity;
	int wallWidth = 75;
public:
	RougeRock(Renderer* rend, const char* path, bool _collisionDet, float gravity = 0) : Sprite(rend, path, _collisionDet)
	{
		_gravity = gravity;
		_velocity = { 0,0 };
		_position = { getPosX(), getPosY() };
		_positionF = { 1, 1 };
	}

	virtual void update(SDL_Renderer* rend)
	{
		Sprite::update(rend);

		//Smooth Acceleration
		_velocity.y -= _gravity;

		//Smooth Velocity
		_position.x -= (int)_velocity.x;
		_positionF.x += _velocity.x - (int)_velocity.x;
		if (_positionF.x >= 1) {
			_position.x -= (int)_positionF.x;
			_positionF.x -= (int)_positionF.x;
		}
		_position.y -= (int)_velocity.y;
		_positionF.y += _velocity.y - (int)_velocity.y;
		if (_positionF.y >= 1) {
			_position.y -= (int)_positionF.y;
			_positionF.y -= (int)_positionF.y;
		}
		setPos({ _position.x, _position.y });
		reSpawnTop();
		getCol()->setBoundBox();
	}

	void Spawn(vec::Vec2 pos, vec::Vec2 size) {
		_position = pos;
		this->setSize({ size.x, size.y });
	}

	void reSpawnTop() {
		if (!CheckOutOfBounds())
			return;
		//int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth - rect.w - wallWidth)) + wallWidth);
		int rockType = rand() % 2;
		if (rockType) {
			int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth - rect.w - wallWidth)) + wallWidth);
			Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
			_velocity.y = 10;
			//printf("%d \n", SpAreaX);
		}
		else {
			int spawnPos = rand() % 2;
			if (spawnPos) {
				int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth / 2 - rect.w - wallWidth)) + wallWidth);
				Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
				_velocity.x = -3;
				_velocity.y = 10;
				//printf("%d \n", SpAreaX);
			}
			else {
				int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth / 2 - rect.w - wallWidth)) + Global::ScreenWidth / 2);
				Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
				_velocity.x = 3;
				_velocity.y = 10;
				//printf("%d \n", SpAreaX);
			}
		}
	}

	bool CheckOutOfBounds()
	{
		if (rect.y > Global::ScreenHeight) {
			return true;
		}
		return false;
	}

	inline void setWallWidth(int _width) {
		wallWidth = _width;
	}
};

class RogueBalloon :
	public Sprite
{
public:
	RogueBalloon(Renderer* rend, const char* path, bool _collisionDet, int gravity = 0) :Sprite(rend, path, _collisionDet),
		_velocity({ 0,0 }), _gravity(gravity / 1.2f)
	{
		_position = { getPosX(), getPosY() };
	}

	inline void setWallWidth(int _width) {
		wallWidth = _width;
	}

	void Spawn(vec::Vec2 Pos, vec::Vec2 Size) {
		setWidth(Size.x);
		setHeight(Size.y);
		setPosX(Pos.x);
		setPosY(Pos.y);
	}

	void reSpawnTop() {

		if (!CheckOutOfBounds())
			return;

		//printf("Hai Out");
		// (rand() % (ub - lb + 1)) + lb
		int SpAreaX = (rand() % (wallWidth - (Global::ScreenWidth - rect.w - wallWidth)) + wallWidth);
		Spawn({ SpAreaX ,-rect.y }, { rect.w,rect.h });
		_velocity.y = (_velocity.y - 20) / 2;
		//printf("%d \n", SpAreaX);
	}

	bool CheckOutOfBounds()
	{
		if (rect.y > Global::ScreenHeight) {
			//printf("%d %d\n",rect.y, Global::ScreenHeight);
			return true;
		}
		return false;
	}

	virtual void update(SDL_Renderer* rend)
	{
		srand(SDL_GetTicks());
		Sprite::update(rend);
		_velocity.y -= _gravity / 60;
		//printf("%f\n", _fraction.y);



		//Smooth Velocity
		//printf("%f %f\n", _velocity.x, _velocity.y);
		_position.x -= (int)_velocity.x;
		_positionF.x += _velocity.x - (int)_velocity.x;
		if (_positionF.x >= 1) {
			_position.x -= (int)_positionF.x;
			_positionF.x -= (int)_positionF.x;
		}
		_position.y -= (int)_velocity.y;
		_positionF.y += _velocity.y - (int)_velocity.y;
		if (_positionF.y >= 1) {
			_position.y -= (int)_positionF.y;
			_positionF.y -= (int)_positionF.y;
		}


		setPos({ _position.x, _position.y });
		//printf("%f\n",_velocity.y);
		reSpawnTop();

		getCol()->setBoundBox();

	}
	//void Spaw

private:
	int wallWidth = 75;
	vec::Vec2f _velocity = { 0,0 };
	vec::Vec2 _position;
	vec::Vec2f _positionF = { 1, 1 };
	float _gravity;

};

class Wall : public Sprite {
private:
	int _velocity;
public:
	Wall(Renderer* rend, const char* path, bool _collisionDet, float velocity = 0) : Sprite(rend, path, _collisionDet)
	{
		_velocity = velocity;
	}
	virtual void update(SDL_Renderer* rend)
	{
		Sprite::update(rend);
		setPos({ getPosX(), getPosY() + _velocity});
		reSpawnTop();
		getCol()->setBoundBox();
	}

	void Spawn(vec::Vec2 pos, vec::Vec2 size) {
		this->setPos({ pos.x, pos.y });
		this->setSize({ size.x, size.y });
	}

	void reSpawnTop() {
		if (!CheckOutOfBounds())
			return;
		Spawn({ rect.x ,-rect.y }, { rect.w,rect.h });
	}

	bool CheckOutOfBounds()
	{
		if (rect.y > Global::ScreenHeight) {
			return true;
		}
		return false;
	}
};

Game::Game(unsigned int w, unsigned int h, const char* t) {
	_width = w;
	_height = h;
	_title = t;
	_render_flags = SDL_RENDERER_ACCELERATED;
	_isGameClosed = false;
	_fps = 60;
	Global::ScreenHeight = _height;
	Global::ScreenWidth = _width;
	error::checkReturnCode(SDL_Init(SDL_INIT_EVERYTHING));

	_window = (SDL_Window*)error::checkReturnPointer(SDL_CreateWindow(
		_title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_width, _height, 0));

	_renderer = new Renderer(_window, _render_flags);
	_eventhandler = new EventHandler();
	_lastFrameTick = SDL_GetTicks64();
}

int Game::getTicks() {
	return (SDL_GetTicks64() - _lastFrameTick);
}

void Game::_init() {
}

void Game::update() {
	RougeRock rok(_renderer, "src/Assets/airgunfire.png", true, 10.0f / 60);
	rok.setPos({ 100, 100 });
	rok.setSize({ 50, 50 });


	RogueBalloon bal(_renderer, "src/Assets/Wallpaper.png", true, 10);
	bal.setPos({ 500,500 });
	bal.setSize({ bal.getWidth() / 6 ,bal.getHeight() / 6 });

	//Wall wall(_renderer, "src/assets/Wallpaper.png", true, 10);
	//wall.setPos({ 0, 0 });
	//wall.setSize({75, 720});

	Wall* leftwalls[3];
	for (int i = 0; i < 3; i++) {
		leftwalls[i] = new Wall(_renderer, "src/assets/Wallpaper.png", true, 10);
		leftwalls[i]->setPos({0, -i * Global::ScreenHeight});
		leftwalls[i]->setSize({Global::wallWidth, Global::ScreenHeight});
	}

	Wall* rightwalls[3];
	for (int i = 0; i < 3; i++) {
		rightwalls[i] = new Wall(_renderer, "src/assets/Wallpaper.png", true, 10);
		rightwalls[i]->setPos({Global::ScreenWidth - Global::wallWidth, -i * Global::ScreenHeight});
		rightwalls[i]->setSize({Global::wallWidth, Global::ScreenHeight});
	}

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double dt = 0;
	Player player(_renderer, "src/Assets/bird1.png", true, _eventhandler, 640, 50, 0.1, 3.0f);

	while (!_isGameClosed) {
		_renderer->ClearScreen();
		_renderer->update();

		SDL_Event event;
		_eventhandler->setInput(&event);
		_isGameClosed = _eventhandler->isQuit();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		dt = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		float currentFPS = 1000.0 / dt;
		player.getDt(dt);
		
		SDL_Delay(1000 / _fps);
		_lastFrameTick = SDL_GetTicks64();
	}

	for (int i = 0; i < 3; i++) {
		delete leftwalls[i];
		delete rightwalls[i];
	}
}

Game::~Game() {
	delete _eventhandler;
	delete _renderer;
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
