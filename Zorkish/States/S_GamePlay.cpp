#include "HeaderFiles/States/States.h"
#include "HeaderFiles/Game/UtilityFunctions.h"

using namespace std;

void S_GamePlay::render() {
    if (!GameManger::Instance()->loaded()){
        loadWorld();
    }
    cout << "\nYou are in the " << GM::Instance()->map()->GetPlayerLocation()->getName() << ":" << endl;
    cout << ":> ";

}

state S_GamePlay::execute(string command) {
    command = UtilityFunctions::ToLower(command);
    if (command == "quit") {
        return State_Menu;
    }
    else if (command == "hiscore") {
        return State_High;
    }
    else if (CommandParse::CheckForCommand(command)){
        CommandParse::ParseCommand(command);
    }
    else {
        cout << "Not a Valid Command" << endl;
    }
    return State_GamePlay;
}

void S_GamePlay::loadWorld() {
    GM::Instance()->loadWorld();
}
