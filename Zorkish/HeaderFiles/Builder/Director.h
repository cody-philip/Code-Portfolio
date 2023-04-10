#ifndef ZORKISH_DIRECTOR_H
#define ZORKISH_DIRECTOR_H

#include "LivingEntityBuilder.h"
#include "StaticEntityBuilder.h"

class Director {
public:
    Director() = default;

    static void constructPlayer(LivingEntityBuilder* builder, const std::string& name, const std::string& desc, int hp);
    static void constructMonster(LivingEntityBuilder* builder, const std::string& name, const std::string& desc, int hp);
    static void constructItem(StaticEntityBuilder* builder, const std::string& name, const std::string& desc);
    static void constructContainer(StaticEntityBuilder* builder, const std::string& name, const std::string& desc);
};

#endif //ZORKISH_DIRECTOR_H
