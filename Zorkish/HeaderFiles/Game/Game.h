#pragma once
#include "StateManager.h"
#include "HeaderFiles/Commands/Invoker.h"

class Game {
private:
	bool exit;
	std::string command, lastCommand;
	StateManager* manager;

public:
	explicit Game(StateManager* tmp);

	void update();
	void render();
    void runGame();
};