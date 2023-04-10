#include "HeaderFiles/States/States.h"
#include "HeaderFiles/Game/UtilityFunctions.h"

using namespace std;

void S_SelectAdventure::render() {
    string tmp;
	cout << "\n\tZorkish :: Select Adventure" << endl;
	cout << "--------------------------------------------\n" << endl;
    cout << "List of Adventure files in the Adventures directory: " << endl;
    for (const auto & entry: fs::directory_iterator("./Adventures")) {
        tmp = entry.path().string();
        cout << "\t> " << UtilityFunctions::TrimExtension(tmp) << endl;
    }
    cout << "Choose Adventure" << endl;
    cout << ":> ";
}

state S_SelectAdventure::execute(string command) {
	if (command == "quit") {
		return State_Quit;
	}
	else {
        ifstream file("./Adventures/" + command + ".txt");
        if (file.is_open()){
            GameManger::Instance()->updateAdventure(command);
            return State_GamePlay;
        }
        cout << "Invalid Command" << endl;
        return State_SelectAdventure;
    }
}