#include "HeaderFiles/States/States.h"

using namespace std;

void S_MainMenu::render() {
	cout << "\n\tZorkish :: Main Menu" << endl;
	cout << "--------------------------------------------\n" << endl;
	cout << "Welcome to Zorkish Adventures\n" << endl;
	cout << "\t1. Select Adventure and Play" << endl;
	cout << "\t2. Hall of Fame" << endl;
	cout << "\t3. S_Help" << endl;
	cout << "\t4. S_About" << endl;
	cout << "\t5. Quit\n" << endl;
	cout << "Select 1-5:> ";

}

state S_MainMenu::execute(string command) {
	if (command == "quit" || command == "5") {
		return State_Quit;
	}
	else if (command == "1") {
		return State_SelectAdventure;
	}
	else if (command == "2") {
		return State_Hall;
	}
	else if (command == "3") {
		return State_Help;
	}
	else if (command == "4") {
		return State_About;
	}
	else {
		cout << "Not a Valid Command" << endl;
		return State_Menu;
	}

}