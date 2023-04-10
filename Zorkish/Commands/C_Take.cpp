#include "HeaderFiles/Commands/Commands.h"

void C_Take::Execute() const {
    _location->GetInventory()->removeItem(_item);
    _player->getInventory()->addItem(_item);
    std::cout << "Picked up " << _item->getName() << endl;
}