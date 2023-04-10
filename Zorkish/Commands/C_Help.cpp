#include "HeaderFiles/Commands/Commands.h"

using namespace std;

void C_Help::Execute() const {
    map<string, vector<string>> commandtoalias;

    for (const auto& d: (*_dict)) {
        commandtoalias[d.second].push_back(d.first);
    }

    string aliases;
    cout << "Known commands: " << endl;
    for (const auto& v: commandtoalias) {
        cout << " > " << UtilityFunctions::Capitalise(v.first) << endl;
        if(v.first == "alias"){
            cout << "Description: Allows you to make an alias for a command." << endl;
            cout << "Syntax: alias [known_command] [alias]" << endl;
        }
        else if(v.first == "debug_tree"){
            cout << "Description: Prints all objects/entities in the graph map." << endl;
            cout << "Syntax: debug_tree" << endl;
        }
        else if(v.first == "go"){
            cout << "Description: Moves the _player." << endl;
            cout << "Syntax: go [direction]" << endl;
            cout << "Syntax: [direction]" << endl;
        }
        else if(v.first == "help"){
            cout << "Description: Prints all known commands." << endl;
            cout << "Syntax: help" << endl;
        }
        else if(v.first == "inventory"){
            cout << "Description: Prints the _contents of the players inventory." << endl;
            cout << "Syntax: inventory" << endl;
        }
        else if(v.first == "look"){
            cout << "Description: Prints the getDescription of the room that the _player is in as well as a list of entities in the room." << endl;
            cout << "Syntax: look [entity]" << endl;
        }
        else if(v.first == "look at"){
            cout << "Description: Prints a detailed getDescription of an entity within the players location (including _player inventory)." << endl;
            cout << "Syntax: look at [entity]" << endl;
        }
        else if(v.first == "look in"){
            cout << "Description: Allows you to make an alias for a command." << endl;
            cout << "Syntax: Work in progress" << endl;
        }

        for (const auto& s: v.second) {
            aliases += s + ", ";
        }
        aliases.pop_back();
        aliases.pop_back();
        cout << "Known Aliases: " << aliases << endl;
        aliases = "";
    }
}