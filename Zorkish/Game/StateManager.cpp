#include "HeaderFiles/Game/StateManager.h"

#include <utility>

using namespace std;

StateManager::StateManager() {
	currentState = State_Menu;
	StateTable[State_Menu] = new S_MainMenu();
	StateTable[State_About] = new S_About();
	StateTable[State_Help] = new S_Help();
	StateTable[State_Hall] = new S_HallOfFame();
	StateTable[State_SelectAdventure] = new S_SelectAdventure();
	StateTable[State_GamePlay] = new S_GamePlay();
	StateTable[State_High] = new S_HiScore();
}

void StateManager::render() {
	StateTable[currentState]->render();
}

void StateManager::execute(string command) {
	// need to add in conditions for _player pressing esc and or enter keys
	currentState = StateTable[currentState]->execute(std::move(command));
}

state StateManager::getState() {
	return currentState;
}