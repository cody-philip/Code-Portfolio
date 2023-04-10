#include "HeaderFiles/States/States.h"

using namespace std;

void S_About::render() {
	cout << "\n\tZorkish :: S_About" << endl;
	cout << "--------------------------------------------\n" << endl;
	cout << "\nWritten by: Cody Philip" << endl;
	cout << "\nPress ESC or Enter to return to Main Menu\n" << endl;
}

state S_About::execute(string command) {
	if (command == "quit") {
		return State_Quit;
	}
	else {
		return State_Menu;
	}
}