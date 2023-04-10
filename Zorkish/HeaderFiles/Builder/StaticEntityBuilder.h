#ifndef ZORKISH_STATICENTITYBUILDER_H
#define ZORKISH_STATICENTITYBUILDER_H

#include <string>

class StaticEntityBuilder {
public:
    virtual void Reset() = 0;

    virtual void setName(const std::string& name) = 0;
    virtual void setDescription(const std::string& desc) = 0;
};

#endif //ZORKISH_STATICENTITYBUILDER_H
