#ifndef ZORKISH_ITEM_H
#define ZORKISH_ITEM_H

#include <utility>

#include "HeaderFiles/Entities/Static.h"

class Item : public Static {
public:
    explicit Item(std::string name, std::string desc) : Static(std::move(name), std::move(desc)){}
    explicit Item() : Static("", "") {}
};

#endif //ZORKISH_ITEM_H
