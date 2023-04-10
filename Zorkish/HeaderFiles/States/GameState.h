#pragma once
#include <string>
#include "Types.h"

class GameState {
public:
	virtual void render() = 0;
	virtual state execute(std::string command) = 0;
};
