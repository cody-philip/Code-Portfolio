#ifndef ZORKISH_CONTAINER_H
#define ZORKISH_CONTAINER_H

#include <utility>

#include "Item.h"
#include "HeaderFiles/Entities/Components/Inventory.h"

class Container : public Static {
private:
    // TODO: Add a component for isOpen

    Inventory _inv;

public:
    explicit Container(std::string name, std::string desc) : Static(std::move(name), std::move(desc)){ _inv = Inventory(); }
    explicit Container() : Static("", "") {}
    //~Container() { std::cout << _name << " is being destroyed." << std::endl; }

    Inventory* getInventory() { return &_inv; }
};

#endif //ZORKISH_CONTAINER_H
