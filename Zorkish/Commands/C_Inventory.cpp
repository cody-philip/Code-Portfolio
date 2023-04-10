#include "HeaderFiles/Commands/Commands.h"

void C_Inventory::Execute() const {
    std::cout << "Inventory List:" << std::endl;
    _player->ViewInventory();
}