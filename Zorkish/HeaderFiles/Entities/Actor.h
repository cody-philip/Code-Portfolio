#ifndef ZORKISH_ACTOR_H
#define ZORKISH_ACTOR_H

#include "HeaderFiles/Entities/Components/Inventory.h"
#include <HeaderFiles/Entities/Living.h>
#include <HeaderFiles/Entities/Entity.h>

#include <utility>

class Actor : public Living{
private:
    Inventory _inv;

public:
    explicit Actor(std::string name, std::string desc) : Living(std::move(name), std::move(desc)) { _inv = Inventory(); }
    explicit Actor() : Living("", "") { _inv = Inventory(); }
    ~Actor();

    void ViewInventory();
    Inventory* getInventory() {return &_inv;}
};


#endif //ZORKISH_ACTOR_H
