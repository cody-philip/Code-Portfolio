/*#include "Commands.h"

void C_Alias::Execute() const {
    std::cout << "Aliasing: " << _map << " has been linked to the " << _com << " command" << std::endl;
    _dict->insert(std::pair<std::string, std::string>(_map, _com));
}

void C_DebugTree::Execute() const {
    std::cout << "Start of the Debug Tree: " << std::endl;
    _map->PrintGraph();
}

void C_Go::Execute() const {
    std::cout << "Moving " << UtilityFunctions::Capitalise(_direction) << std::endl;
    _wg->MovePlayerByDirection(_direction);
}

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
            cout << "Description: Prints the description of the room that the _player is in as well as a list of entities in the room." << endl;
            cout << "Syntax: look [entity]" << endl;
        }
        else if(v.first == "look at"){
            cout << "Description: Prints a detailed description of an entity within the players location (including _player inventory)." << endl;
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

void C_Inventory::Execute() const {
    std::cout << "Inventory List:" << std::endl;
    _player->ViewInventory();
}

void C_Look::Execute() const {
    std::cout << _loc->GetPlayerLocation()->description() << std::endl;
    std::cout << "There are several exits to this room:"  << std::endl;
    _loc->PrintPlayerDirections();
    if (_loc->GetPlayerLocation()->GetInventory()->GetInventory().size() > 0){
        std::cout << "There are some items in the area: " << std::endl;
        _loc->GetPlayerLocation()->getInventory()->DisplayInventory();
    }
}

void C_LookAt::Execute() const {
    std::cout <<  UtilityFunctions::Capitalise(_ent->getName()) << ": " << _ent->getDescription() << std::endl;
}*/