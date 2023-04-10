#pragma once
#include <string>
#include <vector>
#include <utility>

#include "HeaderFiles/Entities/Components/Inventory.h"

class Location : public Entity {
private:
    Inventory _inv;

public:
    explicit Location(std::string name, std::string desc);
    ~Location() = default;

    [[nodiscard]] Inventory* GetInventory();
};