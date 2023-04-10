#include "HeaderFiles/Game/Game.h"

using namespace std;

int main() {
	StateManager manager;
	Game game(&manager);

	game.runGame();

	return 0;

}