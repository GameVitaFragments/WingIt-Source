#pragma once
#include "SDL2/SDL.h"
#include "../Error/Error.h"
#include "../Renderer/Renderer.h"
#include "../Event/EventHandler.h"

class Game {
	private:
		unsigned int _width;
		unsigned int _height;
		const char* _title;
		bool _isGameClosed;
		float _fps;

		SDL_Window* _window;
		Renderer* _renderer;
		EventHandler* _eventhandler;

		Uint32 _render_flags;

		void _init();

	public:
		Game(unsigned int, unsigned int, const char*);
		~Game();
		void update();

		inline unsigned int getWidth() { return _width; };
		inline unsigned int getHeight() { return _height; };
		inline float getFPS() { return _fps; };
};
