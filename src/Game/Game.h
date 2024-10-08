#pragma once
#include "SDL2/SDL.h"
#include "../Error/Error.h"
#include "../Renderer/Renderer.h"
#include "../Player/Player.h"
#include "../Sprite/Sprite.h"
#include "../Event/EventHandler.h"
#include "../Audio/Audio.h"
#include "../StaticText/StaticText.h"

class Game {
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

		void _init();

	public:
		Game(unsigned int w, unsigned int h, const char* t, SDL_Window* win, Renderer* ren, EventHandler* even);
		~Game();
		void update();

		inline unsigned int getWidth() { return _width; };
		inline unsigned int getHeight() { return _height; };
		inline float getFPS() { return (1 / getTicks()); };
		int getTicks();
};
