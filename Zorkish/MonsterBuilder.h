#ifndef ZORKISH_MONSTERBUILDER_H
#define ZORKISH_MONSTERBUILDER_H

#include "HeaderFiles/Builder/LivingEntityBuilder.h"
#include "HeaderFiles/Entities/Actor.h"

class MonsterBuilder : public LivingEntityBuilder {
private:
    Actor _monster;

public:
    MonsterBuilder();

    void Reset() override;

    void setName(const std::string &name) override;
    void setDescription(const std::string &desc) override;

    void addHealthAttribute(int hp) override;

    Actor getProduct();
};

#endif //ZORKISH_MONSTERBUILDER_H
