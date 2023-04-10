#include "HeaderFiles/Entities/Actor.h"

Actor::~Actor() = default;

void Actor::ViewInventory() {
    _inv.DisplayInventory();
}