#pragma once
#include "SDL2/SDL.h"
#include "../Renderer/Renderer.h"

class Game {
	private:
		unsigned int _width;
		unsigned int _height;
		const char* _title;
		bool _isGameClosed;
		float _fps;

		SDL_Window* _window;
		//SDL_Renderer* _renderer;
		Renderer* _renderer;

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
