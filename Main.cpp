#include<stdio.h>
#include "src/Game/Game.h"

int main(int argc, char* argv[]) {
	Game game(1280, 720, "Game");
	game.update();
	return 0;
}