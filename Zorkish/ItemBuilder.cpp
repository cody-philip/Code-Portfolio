#include "ItemBuilder.h"

ItemBuilder::ItemBuilder() {
    _item = Item();
}

void ItemBuilder::Reset() {
    _item = Item();
}

void ItemBuilder::setName(const std::string& name) {
    _item.setName(name);
}

void ItemBuilder::setDescription(const std::string& desc) {
    _item.setDescription(desc);
}

Item ItemBuilder::getProduct() {
    Item product = _item;
    Reset();
    return product;
}
