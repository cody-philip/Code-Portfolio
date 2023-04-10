#ifndef ZORKISH_ATTACK_H
#define ZORKISH_ATTACK_H

#include <iostream>
#include "HeaderFiles/Entities/Living.h"
#include "HeaderFiles/Entities/Components/Action.h"

class Attack : public Action {
public:
    void actOnLiving(Living *target) override;
};

#endif //ZORKISH_ATTACK_H
