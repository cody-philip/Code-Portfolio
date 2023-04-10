#pragma once

#include "HeaderFiles/Commands/Command.h"
#include "WorldGraph.h"
#include "HeaderFiles/Entities/Actor.h"
#include "Item.h"
#include "Container.h"

#include <string>
#include <utility>
#include <map>
#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

struct Pair{
    std::string key, value;
};

class GameManger {
protected:
    explicit GameManger();

    static GameManger* _gameManager;

    std::string _adventure;
    bool _loaded{};
    std::map<std::string, Command*> _commands;
    std::map<std::string, std::string> _dictionary;
    std::map<std::string, std::string> _directions;

private:
    Actor _player;
    WorldGraph _map;

public:
    GameManger(GameManger( &other)) = delete;
    void operator=(const GameManger &) = delete;

    static GameManger *Instance();

    void updateAdventure(std::string filename);
    std::string getAdventure ();
    void registerCommand(const std::string& call, Command *com);
    bool checkForCommandInMap(const std::string& com);
    Command* getCommandFromMap(const std::string& com);
    void addToDictionary(const std::string& key, std::string value);
    void loadWorld();
    bool inDictionary(const std::string& cmp);
    Entity* searchForEntity(const std::string& cmp);
    Container* searchForContainer(const std::string& cmp);
    Static* searchForStatic(const string& cmp);
    void setPlayer(const Actor& p);

    [[nodiscard]] std::string adventure() const{ return _adventure;}
    [[nodiscard]] bool loaded() const{ return _loaded;}
    [[nodiscard]] std::map<std::string, Command*> commands() const{ return _commands;}
    [[nodiscard]] std::map<std::string, std::string>* dictionary() { return &_dictionary;}
    [[nodiscard]] std::map<std::string, std::string>* directions() { return &_directions;}
    [[nodiscard]] WorldGraph* map() { return &_map;}
    [[nodiscard]] Actor* player() { return &_player;}

};

