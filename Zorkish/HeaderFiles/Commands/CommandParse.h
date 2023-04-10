#ifndef ZORKISH_COMMANDPARSE_H
#define ZORKISH_COMMANDPARSE_H

#include "HeaderFiles/Game/GameManager.h"
#include "Invoker.h"
#include "HeaderFiles/Game/UtilityFunctions.h"

#include <string>
#include <vector>
#include <iostream>

using GM = GameManger;

class Inventory;

class CommandParse {
public:

    static bool CheckForCommand(const std::string& cmd);
    static void ParseCommand(const std::string& cmd);
    static vector<string> GetParametersFromString(const std::string& cmd);
    static string checkForSecondArg(const vector<string>& breakdown, const string& type);
};


#endif //ZORKISH_COMMANDPARSE_H
