#ifndef ZORKISH_ITEMBUILDER_H
#define ZORKISH_ITEMBUILDER_H

#include "HeaderFiles/Builder/StaticEntityBuilder.h"
#include "Item.h"

class ItemBuilder : public StaticEntityBuilder {
private:
    Item _item;

public:
    ItemBuilder();
    void Reset() override;

    void setName(const std::string& name) override;
    void setDescription(const std::string& desc) override;

    Item getProduct();
};

#endif //ZORKISH_ITEMBUILDER_H
