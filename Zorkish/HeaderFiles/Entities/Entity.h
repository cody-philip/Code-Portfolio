#ifndef ZORKISH_ENTITY_H
#define ZORKISH_ENTITY_H

#include <string>
#include <iostream>
#include <map>
#include <utility>
#include <HeaderFiles/Entities/Components/Action.h>

class Entity {
protected:
    std::string _name;
    std::string _description;
    std::map<std::string, Action> _actions;

public:
    explicit Entity(std::string name, std::string desc) : _name(std::move(name)), _description(std::move(desc)){}
    //~Entity() { std::cout << _name << " is being destroyed." << std::endl; }

    [[nodiscard]] virtual std::string getName() const { return _name;}
    [[nodiscard]] virtual std::string getDescription() const { return _description;}

    void setName(std::string name) { _name = std::move(name); }
    void setDescription(std::string desc) { _description = std::move(desc); }

    void addAction(const std::string& actName, Action act) { if (_actions.count(actName) == 0) _actions[actName] = std::move(act); }
};

#endif //ZORKISH_ENTITY_H
