#include"Tetris.h"

int main() {

	Game<Cube, Tetris> game;
	game.obj.setter(&game);
	game.main_loop();
	return 0;
}