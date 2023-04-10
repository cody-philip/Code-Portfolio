#include "HeaderFiles/Commands/CommandParse.h"

#include "HeaderFiles/Commands/Commands.h"

using namespace std;

bool CommandParse::CheckForCommand(const std::string& cmd) {
    vector<string> breakdown = UtilityFunctions::Split(cmd);
    if (GM::Instance()->inDictionary(breakdown[0])) {
        return true;
    }
    return false;
}

vector<string> CommandParse::GetParametersFromString(const std::string& cmd) {
    vector<string> breakdown = UtilityFunctions::Split(cmd);
    vector<string> command;
    int count = 0;
    command.emplace_back("");
    if (GM::Instance()->dictionary()->at(breakdown[0]) == "go") {
        breakdown[0] = "go";
        for (const auto& i : breakdown) {
            if (i != "go") {
                command[count] += i + " ";
            }
        }
        command[count].pop_back();
    }
    else if (breakdown[0] == "look") {
        for (const auto& l : breakdown) {
            if (l != "look" && l != "at" && l != "in") {
                command[count] += l + " ";
            }
        }
        command[count].pop_back();
    }
    else if (breakdown[0] == "take") {
        for (const auto& e : breakdown) {
            if (e == "from") {
                command[count++].pop_back();
                command.emplace_back("");
            }
            else if (e != "take") {
                command[count] += e + " ";
            }
        }
        command[count].pop_back();
    }
    return command;
}

void CommandParse::ParseCommand(const std::string& cmd) {
    vector<string> breakdown = UtilityFunctions::Split(cmd);
    string command = GM::Instance()->dictionary()->at(breakdown[0]);

    if (command == "go") {
        string com = GM::Instance()->dictionary()->at(breakdown[0]);
        string dir = GM::Instance()->directions()->at(GetParametersFromString(cmd)[0]);
        if (!GM::Instance()->checkForCommandInMap(com + dir)){
            GM::Instance()->registerCommand(com + dir, new C_Go(GM::Instance()->map(), dir));
        }
        Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(com + dir));
    }
    else if (command == "help") {
        if (!GM::Instance()->checkForCommandInMap(breakdown[0])){
            GM::Instance()->registerCommand(breakdown[0], new C_Help(GM::Instance()->dictionary()));
        }
        Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(breakdown[0]));
    }
    else if (command == "inventory") {
        if (!GM::Instance()->checkForCommandInMap(breakdown[0])){
            GM::Instance()->registerCommand(breakdown[0], new C_Inventory(GM::Instance()->player()));
        }
        Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(breakdown[0]));
    }
    else if (command == "look") {
        if (checkForSecondArg(breakdown, "look").empty()) {
            WorldGraph* tmp = GM::Instance()->map();
            if (!GM::Instance()->checkForCommandInMap(breakdown[0] + tmp->GetPlayerLocation()->getName())) {
                GM::Instance()->registerCommand(breakdown[0] + tmp->GetPlayerLocation()->getName(), new C_Look(tmp));
            }
            Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(breakdown[0] + tmp->GetPlayerLocation()->getName()));
        }
        else if (checkForSecondArg(breakdown, "look") == "at") {
            Entity* tmp = GM::Instance()->searchForEntity(GetParametersFromString(cmd)[0]);
            if (tmp != nullptr) {
                std::string n = tmp->getName();
                if (!GM::Instance()->checkForCommandInMap(breakdown[0] + breakdown[1] + n)) {
                    GM::Instance()->registerCommand(breakdown[0] + breakdown[1] + n, new C_LookAt(tmp));
                }
                Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(breakdown[0] + breakdown[1] + n));
            }
            else {
                cout << "Cannot find the item you wish to look at" << endl;
            }
        }
        else if (checkForSecondArg(breakdown, "look") == "in") {
            Container* tmp = GM::Instance()->searchForContainer(GetParametersFromString(cmd)[0]);
            if (tmp != nullptr){
                if (!GM::Instance()->checkForCommandInMap(breakdown[0] + breakdown[1] + tmp->getName())) {
                    GM::Instance()->registerCommand(breakdown[0] + breakdown[1] + tmp->getName(), new C_LookIn(tmp));
                }
                Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(breakdown[0] + breakdown[1] + tmp->getName()));
            }
            else {
                cout << "Cannot find the container you wish to look inside" << endl;
            }
        }
    }
    else if (command == "take") {
        WorldGraph* worldGraph = GM::Instance()->map();
        vector<string> parameters = GetParametersFromString(cmd);
        Static* item;
        Container* container;

        string c;
        for (const auto& b : breakdown){
            c += b;
        }

        if (checkForSecondArg(breakdown, "take").empty()) {
            item = GM::Instance()->searchForStatic(parameters[0]);
            if (!GM::Instance()->checkForCommandInMap(c)) {
                GM::Instance()->registerCommand(c, new C_Take(item, GM::Instance()->player(), worldGraph->GetPlayerLocation()));
            }
            Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(c));
        }
        else if (checkForSecondArg(breakdown, "take") == "from") {
            if (parameters.size() > 1) {
                container = worldGraph->GetContainerByName(parameters[1]);

                if (container != nullptr) {
                    item = dynamic_cast<Static *>(container->getInventory()->GetItem(parameters[0]));
                    if (!GM::Instance()->checkForCommandInMap(c)) {
                        GM::Instance()->registerCommand(c, new C_TakeFrom(item, GM::Instance()->player(), container));
                    }
                    Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(c));
                }
            }
        }
    }
    else if (command == "alias") {
        if (!GM::Instance()->checkForCommandInMap(cmd)) {
            string alias = cmd;
            alias.erase(0, 6);
            string left, right;
            vector<string> subbreakdown = UtilityFunctions::Split(alias);
            if ((subbreakdown[0] == "look" && checkForSecondArg(subbreakdown, std::string()) == "at")
                || (subbreakdown[0] == "look" && checkForSecondArg(subbreakdown, std::string()) == "in")) {
                right = subbreakdown[0] + " " + subbreakdown[1];
                left = GetParametersFromString(alias)[0];
            } else {
                right = subbreakdown[0];
                left = GetParametersFromString(alias)[0];
            }
            GM::Instance()->registerCommand(cmd, new C_Alias(GameManger::Instance()->dictionary(), left, right));
            Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(cmd));
        } else {
            cout << "This Alias has already occurred before." << endl;
        }
    }
    else if (command == "debug_tree") {
        if (!GM::Instance()->checkForCommandInMap(breakdown[0])){
            GM::Instance()->registerCommand(breakdown[0], new C_DebugTree(GM::Instance()->map()));
        }
        Invoker::Instance()->EnqueueCommand(GM::Instance()->getCommandFromMap(breakdown[0]));
    }
}

string CommandParse::checkForSecondArg(const vector<string>& breakdown, const string& type) {
    if (type == "look") {
        for (const auto& e : breakdown) {
            if (e == "at") {
                return "at";
            } else if (e == "in") {
                return "in";
            }
        }
    }
    else if (type == "take") {
        for (const auto& e : breakdown) {
            if (e == "from") {
                return "from";
            }
        }
    }
    return "";
}
