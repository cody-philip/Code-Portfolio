#pragma once

#include "HeaderFiles/States/States.h"

#include <map>
#include <iostream>
#include <string>

class StateManager {
private:
	std::map<state, GameState*>StateTable;
	state currentState;

public:
	StateManager();
	state getState();
	void render();
	void execute(std::string command);

};