#include "HeaderFiles/Commands/Commands.h"

void C_Look::Execute() const {
    std::cout << _loc->GetPlayerLocation()->getDescription() << std::endl;
    std::cout << "There are several exits to this room:"  << std::endl;
    _loc->PrintPlayerDirections();
    // TODO: Extend location inventory display
    if (!_loc->GetPlayerLocation()->GetInventory()->GetInventory()->empty()){
        std::cout << "There are some items in the area: " << std::endl;
        _loc->GetPlayerLocation()->GetInventory()->DisplayInventory();
    }
}