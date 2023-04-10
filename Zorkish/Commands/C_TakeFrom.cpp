#include "HeaderFiles/Commands/Commands.h"

void C_TakeFrom::Execute() const {
    _container->getInventory()->removeItem(_item);
    _player->getInventory()->addItem(_item);
    std::cout << "Taken " << _item->getName() << " from " << _container->getName() << endl;
}