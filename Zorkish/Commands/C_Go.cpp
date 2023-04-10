#include "HeaderFiles/Commands/Commands.h"

void C_Go::Execute() const {
    std::cout << "Moving " << UtilityFunctions::Capitalise(_direction) << std::endl;
    _wg->MovePlayerByDirection(_direction);
}