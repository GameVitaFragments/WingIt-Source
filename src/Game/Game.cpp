#include "Game.h"
#include <iostream>

namespace ui {
	class Button : public Sprite {
	private:
		float maxSizeRatio = 1.3;
		float minSizeRatio = 1.0;
		float initialWidth;
		float initialHeight;

	public:
		Button(Renderer* rend, const char* path, bool _collisionDet) : Sprite(rend, path, _collisionDet) {
			initialWidth = 300;
			initialHeight = 200;
			setSize({ (int)initialWidth, (int)initialHeight });
		}

		void hover(int mx, int my) {
			if (mx > getPosX() && mx < (getPosX() + getWidth()) && my > getPosY() && my < (getPosY() + getHeight())) {
				if (getWidth() < (maxSizeRatio * initialWidth)) {
					float dx = ((maxSizeRatio * initialWidth) - getWidth());
					setWidth(getWidth() + dx);
					setPosX(getPosX() - dx / 2.0);
				}
				if (getHeight() < (maxSizeRatio * initialHeight)) {
					float dx = ((maxSizeRatio * initialHeight) - getHeight());
					setHeight(getHeight() + dx);
					setPosY(getPosY() - dx / 2.0);
				}
			}
			else {
				if (getWidth() > initialWidth) {
					float dx = getWidth() - initialWidth;
					setWidth(getWidth() - dx);
					setPosX(getPosX() + dx / 2.0);
				}
				if (getHeight() > initialHeight) {
					float dx = getHeight() - initialHeight;
					setHeight(getHeight() - dx);
					setPosY(getPosY() + dx / 2.0);
				}
			}
		}
	};
}

class RougeRock :
	public Sprite
{
private:
	vec::Vec2 _velocity;
	int _gravity;
public:
	RougeRock(Renderer* rend, const char* path, bool _collisionDet, int gravity = 0, vec::Vec2 velocity = { 0,0 }) : Sprite(rend, path, _collisionDet),
		_velocity(velocity), _gravity(gravity)
	{
	}

	virtual void update(SDL_Renderer* rend)
	{
		Sprite::update(rend);
		_velocity.y -= _gravity;
		setPos({ getPosX() - _velocity.x, getPosY() - _velocity.y });
		getCol()->setBoundBox();
	}
};

class RogueBalloon :
	public Sprite
{
public:
	RogueBalloon(Renderer* rend, const char* path, bool _collisionDet, int gravity=0) :Sprite(rend, path, _collisionDet),
		_velocity({ 0,0}), _gravity(gravity)
	{

	}

	virtual void update(SDL_Renderer* rend)
	{
		Sprite::update(rend);
		_velocity.y -= _gravity/60;
		printf("%f\n", _velocity.y);
		setPos({ getPosX() - (int)_velocity.x,getPosY() - (int)_velocity.y });
		getCol()->setBoundBox();

	}
	//void Spaw

private:
	vec::Vec2f _velocity = { 0,0 };
	float _gravity;


};

Game::Game(unsigned int w, unsigned int h, const char* t) {
	_width = w;
	_height = h;
	_title = t;
	_render_flags = SDL_RENDERER_ACCELERATED;
	_isGameClosed = false;
	_fps = 60;

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
	RougeRock rok(_renderer, "src/Assets/airgunfire.png", true, 10, { 1, 0 });
	rok.setPos({ 100, 100 });
	rok.setSize({ 50, 50 });

	RogueBalloon bal(_renderer, "src/Assets/Wallpaper.png", true, -1);
	bal.setPos({ 500,500 });
	bal.setSize({ bal.getWidth() / 6 ,bal.getHeight() / 6 });

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double dt = 0;

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
		
		SDL_Delay(1000 / _fps);
		_lastFrameTick = SDL_GetTicks64();
	}
}

Game::~Game() {
	delete _eventhandler;
	delete _renderer;
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
