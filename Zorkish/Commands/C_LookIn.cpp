#include "HeaderFiles/Commands/Commands.h"

void C_LookIn::Execute() const {
    // TODO: Extend to check if container isOpen
    std::cout << "The " << _container->getName() << " contains: \n";
    _container->getInventory()->DisplayInventory();
}