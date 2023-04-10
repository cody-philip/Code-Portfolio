#include "HeaderFiles/Game/GameManager.h"

#include <utility>

using namespace std;

GameManger* GameManger::_gameManager = nullptr;

GameManger::GameManger() {
    ifstream file("./Commands/aliases.txt");
    string str, key;
    vector<Pair> pairs;
    size_t pos = 0;

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
    }

    while (getline(file, str)){
        while((pos = str.find(':')) != string::npos) {
            key = str.substr(0, pos);
            str.erase(0, pos+1);
            pairs.push_back({key, str});
        }
    }

    file.close();

    for (const auto& v : pairs) {
        _dictionary[v.key] = v.value;
    }

    file.open("./Commands/directions.txt");
    if (!file.is_open()) {
        cout << "Failed to open the file" << endl;
    }

    pos = 0;
    pairs.clear();
    while (getline(file, str)){
        while((pos = str.find(':')) != string::npos) {
            key = str.substr(0, pos);
            str.erase(0, pos+1);
            pairs.push_back({key, str});
        }
    }

    file.close();

    for (const auto& v : pairs) {
        _directions[v.key] = v.value;
    }

    // default _player
    _player =  Actor("Actor", "Actor character");
}

GameManger *GameManger::Instance() {
    if (_gameManager == nullptr){
        _gameManager= new GameManger();
    }
    return _gameManager;
}

void GameManger::updateAdventure(std::string filename) {
    _adventure = std::move(filename);
    _loaded = false;
}

std::string GameManger::getAdventure() {
    _loaded = true;
    return _adventure;
}

void GameManger::registerCommand(const std::string& call, Command *com) {
    _commands[call] = com;
}

bool GameManger::checkForCommandInMap(const std::string& com) {
    return _commands.count(com);
}

Command* GameManger::getCommandFromMap(const std::string& com) {
    return _commands[com];
}

void GameManger::addToDictionary(const std::string& key, std::string value) {
    _dictionary[key] = std::move(value);
}

void GameManger::loadWorld() {
    _map = WorldGraph("./Adventures/" + _adventure + ".txt");
    _loaded = true;
}

bool GameManger::inDictionary(const std::string& cmp) {
    return _dictionary.count(cmp);
}

Entity *GameManger::searchForEntity(const string& cmp) {
    if (_map.GetPlayerLocation()->getName() == cmp) {
        return _map.GetPlayerLocation();
    } else if (_map.GetPlayerLocation()->GetInventory()->GetItem(cmp) != nullptr){
        return _map.GetPlayerLocation()->GetInventory()->GetItem(cmp);
    } else if (_player.getInventory()->GetItem(cmp) != nullptr) {
        return _player.getInventory()->GetItem(cmp);
    }
    return nullptr;
}

void GameManger::setPlayer(const Actor& p) {
    _player = p;
}

Container *GameManger::searchForContainer(const std::string& cmp) {
    Entity* lhs = searchForEntity(cmp);
    Container* rhs = nullptr;
    if (lhs != nullptr) {
        rhs = _map.GetContainerByName(lhs->getName());
    }
    return rhs;
}

Static *GameManger::searchForStatic(const string& cmp) {
    Entity* lhs = searchForEntity(cmp);
    Static* rhs = nullptr;
    if (lhs != nullptr) {
        rhs = _map.GetStaticByName(lhs->getName());
    }
    return rhs;
}
