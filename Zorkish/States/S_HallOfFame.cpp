#include "HeaderFiles/States/States.h"

using namespace std;

void S_HallOfFame::render() {
	cout << "\n\tZorkish :: Hall of Fame" << endl;
	cout << "--------------------------------------------\n" << endl;
	cout << "Top 10 Zorkish Adventure Champions:\n" << endl;
	cout << "\t1. Fred, Mountain World, 5000" << endl;
	cout << "\t2. Mary, Mountain World, 4000" << endl;
	cout << "\t3. Joe, Water World, 3000" << endl;
	cout << "\t4. Henry, Mountain World, 2000" << endl;
	cout << "\t5. Susan, Mountain World, 1000" << endl;
	cout << "\t6. Alfred, Water World, 900" << endl;
	cout << "\t7. Clark, Mountain World, 800" << endl;
	cout << "\t8. Harold, Mountain World, 500" << endl;
	cout << "\t9. Julie, Water World, 300" << endl;
	cout << "\t10. Bill, Box World, -5" << endl;
	cout << "\nPress ESC or Enter to return to Main Menu\n" << endl;
}

state S_HallOfFame::execute(string command) {
	if (command == "quit") {
		return State_Quit;
	}
	else {
		return State_Menu;
	}
}