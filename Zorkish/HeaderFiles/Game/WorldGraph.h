#pragma once
#include <map>
#include <algorithm>
#include <list>

//#include "GameManager.h"
#include <HeaderFiles/Entities/Location.h>
#include <HeaderFiles/Game/AdventureFileReader.h>
#include <HeaderFiles/Entities/Actor.h>
#include "Container.h"

struct Edge {
    std::string scr, dest, exit, entry;
};

struct Direction {
    std::string edge, direction;
};

class GameManger;

class WorldGraph {
private:
    std::map<std::string, std::vector<Direction>> _adjList;
    std::vector<Location*> _locations;
    Location* _playerLocation{};

    list<Container> _containers;
    list<Item> _items;
    list<Actor> _monsters;

public:
    explicit WorldGraph() = default;
    explicit WorldGraph(std::string const& filename);

    void RegisterLocation(Location* loc);
    Location* GetLocationByName(const std::string& name);
    Container* GetContainerByName(const string& name);
    Item* GetItemByName(const string& name);
    Static* GetStaticByName(const string& name);

    void PrintGraph();
    std::vector<Location*>* GetLocations();
    void PrintRoomsConnectedToRoom(const std::string& name);

    Location* GetPlayerLocation();
    void MovePlayerByDirection(const std::string& dir);
    void PrintPlayerDirections();

};