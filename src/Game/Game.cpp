#include "Game.h"
#include "../Error/Error.h"

#include <iostream>

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
}

void Game::_init() {
}

void Game::update() {

	SDL_Texture* tex = Renderer::loadTex(_renderer, "src/Assets/Wallpaper.png");
	SDL_Rect rect;
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;

	while ( !_isGameClosed ) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				_isGameClosed = true;
			}
		}
		SDL_RenderClear(_renderer->GetRenderer());
		SDL_RenderCopy(_renderer->GetRenderer(), tex, NULL, &rect);
		SDL_RenderPresent(_renderer->GetRenderer());
		SDL_Delay(1000 / _fps);
	}
	
	SDL_DestroyTexture(tex);
}

Game::~Game() {
	delete _renderer;
	SDL_DestroyWindow(_window);
	SDL_Quit();
}
