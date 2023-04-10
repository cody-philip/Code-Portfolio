#ifndef ZORKISH_PLAYERBUILDER_H
#define ZORKISH_PLAYERBUILDER_H

#include "LivingEntityBuilder.h"
#include "HeaderFiles/Entities/Actor.h"
#include "Attack.h"

class PlayerBuilder : public LivingEntityBuilder {
private:
    Actor _player;

public:
    PlayerBuilder();

    void Reset() override;

    void setName(const std::string& name) override;
    void setDescription(const std::string& desc) override;

    void addHealthAttribute(int hp) override;

    void addAttackAction() override;

    Actor getProduct();
};

#endif //ZORKISH_PLAYERBUILDER_H
