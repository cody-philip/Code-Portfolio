#include "HeaderFiles/Commands/Commands.h"

void C_DebugTree::Execute() const {
    std::cout << "Start of the Debug Tree: " << std::endl;
    _map->PrintGraph();
}
