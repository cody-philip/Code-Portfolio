#ifndef ZORKISH_LIVINGENTITYBUILDER_H
#define ZORKISH_LIVINGENTITYBUILDER_H

#include <string>

class LivingEntityBuilder {
public:
    virtual void Reset() = 0;

    virtual void setName(const std::string& name) = 0;
    virtual void setDescription(const std::string& desc) = 0;

    virtual void addHealthAttribute(int hp) = 0;

    virtual void addAttackAction(){};
};

#endif //ZORKISH_LIVINGENTITYBUILDER_H
