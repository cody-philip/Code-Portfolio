#ifndef ZORKISH_COMMANDS_H
#define ZORKISH_COMMANDS_H

#include "Command.h"
#include "HeaderFiles/Game/WorldGraph.h"
#include "HeaderFiles/Entities/Actor.h"

#include <string>
#include <iostream>
#include <utility>

class C_Go : public Command {
private:
    WorldGraph *_wg;
    std::string _direction;

public:
    explicit C_Go(WorldGraph *wg, std::string dir) : _wg(wg), _direction(std::move(dir)){}
    void Execute() const override;
};

class C_Help : public Command {
private:
    std::map<std::string, std::string>* _dict;
public:
    explicit C_Help(std::map<std::string, std::string>* dict) : _dict(dict){}
    void Execute() const override;
};

class C_Inventory : public Command {
private:
    Actor *_player;
public:
    explicit C_Inventory(Actor *player) : _player(player){}
    void Execute() const override;
};

class C_Look : public Command {
private:
    WorldGraph* _loc;
public:
    explicit C_Look(WorldGraph *loc) : _loc(loc){}
    void Execute() const override;
};

class C_LookAt : public Command {
private:
    Entity* _ent;
public:
    explicit C_LookAt(Entity* entity) : _ent(entity){}
    void Execute() const override;
};

class C_LookIn : public Command {
private:
    Container* _container;
public:
    explicit C_LookIn(Container* container) : _container(container){}
    void Execute() const override;
};

class C_Take : public Command {
private:
    Static* _item;
    Actor* _player;
    Location* _location;
public:
    explicit C_Take(Static* item, Actor* player, Location* location) : _item(item), _player(player), _location(location) {}
    void Execute() const override;
};

class C_TakeFrom : public Command {
private:
    Static* _item;
    Actor* _player;
    Container* _container;
public:
    explicit C_TakeFrom(Static* item, Actor* player, Container* container) : _item(item), _player(player), _container(container) {}
    void Execute() const override;
};

class C_Alias : public Command {
private:
    std::string _map, _com;
    std::map<std::string, std::string>* _dict;
public:
    explicit C_Alias(std::map<std::string, std::string>* dict, std::string map, std::string com) : _dict(dict), _map(std::move(map)), _com(std::move(com)){}
    void Execute() const override;
};

class C_DebugTree : public Command {
private:
    WorldGraph* _map;

public:
    explicit C_DebugTree(WorldGraph* map) : _map(map){}
    void Execute() const override;
};

#endif //ZORKISH_COMMANDS_H
