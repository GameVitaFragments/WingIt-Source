#include "Error.h"
#include <iostream>
#include "SDL2/SDL.h"

namespace error {
	int checkReturnCode(int code) {
		if (code != 0) {
			std::cout << "[SDL Error] " << SDL_GetError() << std::endl;
		}
		return code;
	}
	void* checkReturnPointer(void* ptr) {
		if (ptr == nullptr) {
			std::cout << "[SDL Error] " << SDL_GetError() << std::endl;
		}
		return ptr;
	}
}
