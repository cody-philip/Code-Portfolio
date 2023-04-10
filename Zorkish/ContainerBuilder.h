#ifndef ZORKISH_CONTAINERBUILDER_H
#define ZORKISH_CONTAINERBUILDER_H

#include "HeaderFiles/Builder/StaticEntityBuilder.h"
#include "Container.h"

class ContainerBuilder : public StaticEntityBuilder {
private:
    Container _container;

public:
    ContainerBuilder();
    void Reset() override;

    void setName(const std::string &name) override;
    void setDescription(const std::string &desc) override;

    Container getProduct();
};

#endif //ZORKISH_CONTAINERBUILDER_H
