#include "HeaderFiles/Entities/Components/Inventory.h"

using namespace std;

Inventory::Inventory() = default;

void Inventory::addItem(Entity* ent) {
    _contents.push_back(ent);
}

void Inventory::removeItem(Entity* ent) {
    int c = 0;
    for (auto ele : _contents) {
        if (ele->getName() == ent->getName()) {
            break;
        }
        c++;
    }

    _contents.erase(_contents.begin() + c);
}

void Inventory::DisplayInventory() {
    if (_contents.empty()) {
        cout << " > Inventory is empty" << endl;
    } else {
        for (auto &item: _contents) {
            cout << " > " << UtilityFunctions::Capitalise(item->getName()) << "\n";
        }
    }
}

Entity *Inventory::GetItem(const std::string& name) {
    for (auto i: _contents) {
        if (UtilityFunctions::ToLower(i->getName()) == name){
            return i;
        }
    }
    return nullptr;
}

Inventory::~Inventory() {
    //std::cout << "Inventory is being destroyed" << std::endl;
    /*for (auto v : _contents) {
        delete v;
    }*/
}
