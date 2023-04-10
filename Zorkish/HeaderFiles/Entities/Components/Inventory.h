#pragma once

#include "HeaderFiles/Entities/Entity.h"
#include "HeaderFiles/Game/UtilityFunctions.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

//class CommandParse;

class Inventory {
private:
    std::vector<Entity*> _contents{};

public:
    explicit Inventory();
    ~Inventory();

    void addItem(Entity* ent);
    void removeItem(Entity* ent);
    void DisplayInventory();
    std::vector<Entity*>* GetInventory() {return &_contents;}
    Entity *GetItem(const std::string&);
};