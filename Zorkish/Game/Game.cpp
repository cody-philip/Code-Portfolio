#include "HeaderFiles/Game/Game.h"

using namespace std;

Game::Game(StateManager* tmp) {
	manager = tmp;
	exit = false;
	command = "";
	lastCommand = "";
}

void Game::runGame() {
	while (!exit) {
		render();
		update();
		if (manager->getState() == State_Quit) {
			exit = true;
		}
	}
}

void Game::update() {
	lastCommand = command;
    getline(cin, command);

	manager->execute(command);
    Invoker::Instance()->Invoke();
}

void Game::render() {
	manager->render();
}