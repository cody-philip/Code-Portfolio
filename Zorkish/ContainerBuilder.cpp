//
// Created by NilFa on 10/26/2022.
//

#include "ContainerBuilder.h"

ContainerBuilder::ContainerBuilder() {
    _container = Container();
}

void ContainerBuilder::Reset() {
    _container = Container();
}

void ContainerBuilder::setName(const std::string &name) {
    _container.setName(name);
}

void ContainerBuilder::setDescription(const std::string &desc) {
    _container.setDescription(desc);
}

Container ContainerBuilder::getProduct() {
    Container product = _container;
    Reset();
    return product;
}
