#include "HeaderFiles/States/States.h"

using namespace std;

void S_Help::render() {
	cout << "\n\tZorkish :: S_Help" << endl;
	cout << "--------------------------------------------\n" << endl;
	cout << "\nThe Following commands are supported:" << endl;
	cout << "\tquit" << endl;
	cout << "\thiscore (for testing)" << endl;
	cout << "\nPress ESC or Enter to return to Main Menu\n" << endl;
}

state S_Help::execute(string command) {
	if (command == "quit") {
		return State_Quit;
	}
	else {
		return State_Menu;
	}
}