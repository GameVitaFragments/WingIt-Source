#include<stdio.h>
#include <SDL2/SDL.h>
#include "src/Game/Game.h"


namespace ui {
	class Button : public Sprite {
	private:
		float maxSizeRatio = 1.3;
		float minSizeRatio = 1.0;
		float initialWidth;
		float initialHeight;
		bool clicked = false;

	public:
		Button(Renderer* rend, const char* path, bool _collisionDet, int scale) : Sprite(rend, path, _collisionDet) {
			setSize({ ((int)getWidth() * scale), ((int)getHeight() * scale) });
			initialWidth = getWidth();
			initialHeight = getHeight();
			setSize({ (int)initialWidth, (int)initialHeight });
		}

		void hover(int mx, int my) {
			if (mx > getPosX() && mx < (getPosX() + getWidth()) && my > getPosY() && my < (getPosY() + getHeight())) {
				if (getWidth() < (maxSizeRatio * initialWidth)) {
					float dx = ((maxSizeRatio * initialWidth) - getWidth());
					setWidth(getWidth() + dx);
					setPosX(getPosX() - dx / 2.0);
				}
				//if (getHeight() < (maxSizeRatio * initialHeight)) {
				//	float dx = ((maxSizeRatio * initialHeight) - getHeight());
				//	setHeight(getHeight() + dx);
				//	setPosY(getPosY() - dx / 2.0);
				//}
			}
			else {
				if (getWidth() > initialWidth) {
					float dx = getWidth() - initialWidth;
					setWidth(getWidth() - dx);
					setPosX(getPosX() + dx / 2.0);
				}
				//if (getHeight() > initialHeight) {
				//	float dx = getHeight() - initialHeight;
				//	setHeight(getHeight() - dx);
				//	setPosY(getPosY() + dx / 2.0);
				//}
			}
		}
	};
}

class MainMenu {
private:
	unsigned int _width;
	unsigned int _height;
	const char* _title;
	bool _isGameClosed;
	float _fps;
	float _lastFrameTick;
	SDL_Window* _window;
	Renderer* _renderer;
	EventHandler* _eventhandler;

	Uint32 _render_flags;
public:
	MainMenu(unsigned int w, unsigned int h, const char* t) {
		_width = w;
		_height = h;
		_title = t;
		_render_flags = SDL_RENDERER_ACCELERATED;
		_isGameClosed = false;
		_fps = 60;

		_window = (SDL_Window*)error::checkReturnPointer(SDL_CreateWindow(
			_title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width, _height, 0));

		_renderer = new Renderer(_window, _render_flags);
		_eventhandler = new EventHandler();
	}
	~MainMenu() {
		delete _eventhandler;
		delete _renderer;
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}
	void update() {
		Uint64 NOW = SDL_GetPerformanceCounter();
		Uint64 LAST = 0;
		double dt = 0;

		Sprite wallpaper(_renderer, "src/Assets/TitleScreen.png", false);
		wallpaper.setPos({ 0, 0 });
		wallpaper.setSize({ (int)_width, (int)_height });

		ui::Button startButton(_renderer, "src/Assets/play1.png", false, 1);
		startButton.setPos({ 100, 600 });

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

			int mx = _eventhandler->getPos('x');
			int my = _eventhandler->getPos('y');

			startButton.hover(mx, my);

			SDL_Delay(1000 / _fps);
			_lastFrameTick = SDL_GetTicks64();
		}
	}
};

int main(int argc, char* argv[]) {
	Game game(1280, 720, "Game");
	game.update();
	//MainMenu mm(1280, 720, "Game");
	//mm.update();
	return 0;
}
