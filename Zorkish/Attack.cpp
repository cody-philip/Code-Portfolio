#include "Attack.h"

void Attack::actOnLiving(Living *target) {
    std::cout << "Attacked " << target->getName() << "!" << std::endl;
}
