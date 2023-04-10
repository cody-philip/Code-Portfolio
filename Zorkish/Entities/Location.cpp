#include <utility>

#include <utility>

#include "HeaderFiles/Entities/Location.h"

Location::Location(std::string name, std::string desc) : Entity(std::move(std::move(name)), std::move(std::move(desc))) {
    _inv = Inventory();
}

Inventory* Location::GetInventory() { return &_inv; }
