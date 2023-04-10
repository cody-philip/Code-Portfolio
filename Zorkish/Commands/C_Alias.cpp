#include "HeaderFiles/Commands/Commands.h"

void C_Alias::Execute() const {
    std::cout << "Aliasing: " << _map << " has been linked to the " << _com << " command" << std::endl;
    _dict->insert(std::pair<std::string, std::string>(_map, _com));
}