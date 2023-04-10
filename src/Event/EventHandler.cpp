#include "EventHandler.h"

void EventHandler::setInput(SDL_Event* event) {
	while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            _quit = true;
            break;
        }
		if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                _quit = true;
                break;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                _w = true;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                _a = true;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                _s = true;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                _d = true;
                break;
            default:
                break;
            }
		}
        if (event->type == SDL_KEYUP) {
            switch (event->key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                _w = false;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                _a = false;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                _s = false;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                _d = false;
                break;
            default:
                break;
            }
        }
        if (event->type == SDL_MOUSEBUTTONDOWN) {
            switch (event->button.button) {
            case SDL_BUTTON_LEFT:
                _m1 = true;
                break;
            case SDL_BUTTON_RIGHT:
                _m2 = true;
                break;
            case SDL_BUTTON_MIDDLE:
                _m3 = true;
                break;
            default:
                break;
            }
        }
        if (event->type == SDL_MOUSEBUTTONUP) {
            switch (event->button.button) {
            case SDL_BUTTON_LEFT:
                _m1 = false;
                break;
            case SDL_BUTTON_RIGHT:
                _m2 = false;
                break;
            case SDL_BUTTON_MIDDLE:
                _m3 = false;
                break;
            default:
                break;
            }
        }
        if (event->type == SDL_MOUSEMOTION) {
            _x = event->motion.x;
            _y = event->motion.y;
        }
	}
}

bool EventHandler::getKBInput(char input) {
    switch (input) {
    case 'w': return _w; break;
    case 'a': return _a; break;
    case 's': return _s; break;
    case 'd': return _d; break;
    default: break;
    }
}

bool EventHandler::getMSInput(char input) {
    switch (input) {
    case '1': return _m1; break;
    case '2': return _m2; break;
    case '3': return _m3; break;
    default: break;
    }
}

int EventHandler::getPos(char input) {
    switch (input) {
    case 'x': return _x; break;
    case 'y': return _y; break;
    default: break;
    }
}

bool EventHandler::isQuit() {
    return _quit;
}