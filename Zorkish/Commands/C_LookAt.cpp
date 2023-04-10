#include "HeaderFiles/Commands/Commands.h"

void C_LookAt::Execute() const {
    std::cout << "Name: " << UtilityFunctions::Capitalise(_ent->getName()) << "\n Description: " << _ent->getDescription() << std::endl;
}