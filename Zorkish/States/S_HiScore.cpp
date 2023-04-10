#include "HeaderFiles/States/States.h"

using namespace std;

void S_HiScore::render() {
	cout << "\n\tZorkish :: New High Score" << endl;
	cout << "--------------------------------------------\n" << endl;
	cout << "\nCongratulations!\n" << endl;
	cout << "You have made it to the Zorkish Hall of Fame\n" << endl;
	cout << "Adventure: Void" << endl;
	cout << "Score: Something" << endl;
	cout << "Moves: Over 9000\n" << endl;
	cout << "Please type your getName and press enter:" << endl;
	cout << ":> ";
}

state S_HiScore::execute(string command) {
	if (command == "quit") {
		return State_Menu;
	}
	else {
        // TODO fix up with additional features
		return State_Menu;
	}

}