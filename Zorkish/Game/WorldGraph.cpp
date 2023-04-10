#include "HeaderFiles/Game/WorldGraph.h"
#include "HeaderFiles/Commands/CommandParse.h"
#include "HeaderFiles/Entities/Entity.h"
#include "HeaderFiles/Game/UtilityFunctions.h"
#include "HeaderFiles/Builder/PlayerBuilder.h"
#include "HeaderFiles/Builder/Director.h"
#include "MonsterBuilder.h"
#include "ItemBuilder.h"
#include "ContainerBuilder.h"

#include <iostream>

using namespace std;

WorldGraph::WorldGraph(const std::string& filename) {
    map<string, map<string, vector<vector<string>>>> file = AdventureFileReader::ReadData(filename);

    for (auto r : file["r"]) {
        RegisterLocation(new Location(r.second[0][0], r.second[0][1]));
    }

    vector<Edge> edges;
    for (const auto& e : file["e"]) {
        for (auto edge : e.second) {
            edges.push_back({edge[0], edge[1], edge[2], edge[3]});
        }
    }
    for (auto &edge : edges) {
        _adjList[edge.scr].push_back({edge.dest, edge.exit});
        _adjList[edge.dest].push_back({edge.scr, edge.entry});
    }

    vector<string> player;
    for (const auto& p : file["p"]) {
        player = p.second[0];
    }
    PlayerBuilder playerBuilder = PlayerBuilder();
    Director::constructPlayer(&playerBuilder, player[0], player[1], stoi(player[2]));
    GameManger::Instance()->setPlayer(playerBuilder.getProduct());

    string locName;
    for (const auto& s : file["s"]) {
        locName = s.first;
    }
    _playerLocation = GetLocationByName(locName);
    _playerLocation->GetInventory()->addItem(GameManger::Instance()->player());

    ContainerBuilder containerBuilder = ContainerBuilder();
    int count = 0;
    for (const auto& c : file["c"]) {
        for (auto con : c.second) {
            Director::constructContainer(&containerBuilder, con[0], con[1]);
            _containers.push_back(containerBuilder.getProduct());
            GetLocationByName(con[2])->GetInventory()->addItem(&_containers.back());
        }
    }

    ItemBuilder itemBuilder = ItemBuilder();
    count = 0;
    for (const auto& i : file["i"]) {
        for (auto item : i.second) {
            Director::constructItem(&itemBuilder, item[0], item[1]);
            _items.push_back(itemBuilder.getProduct());
            if (item[2] == "r") {
                GetLocationByName(item[3])->GetInventory()->addItem(&_items.back());
            } else if (item[2] == "c") {
                GetContainerByName(item[3])->getInventory()->addItem(&_items.back());
            }
        }
    }

    MonsterBuilder monsterBuilder = MonsterBuilder();
    count = 0;
    for (const auto& m: file["m"]) {
        for (auto monster : m.second) {
            Director::constructMonster(&monsterBuilder, monster[0], monster[1], stoi(monster[2]));
            _monsters.push_back(monsterBuilder.getProduct());
            GetLocationByName(monster[3])->GetInventory()->addItem(&_monsters.back());
        }
    }
}

// TODO: Revisit to make better latter
void WorldGraph::PrintGraph() {
    string str;
    for (auto &ele : _adjList) {
        if (ele.first.length() <= 7) {
            cout << ele.first << "\t\t--> ";
        } else {
            cout << ele.first << "\t--> ";
        }

        for (const auto& v : ele.second) {
            str += v.edge + ", ";
        }
        str.pop_back();
        str.pop_back();
        cout << str << endl;
        str = "";

        vector<Entity*>* tmp = GetLocationByName(ele.first)->GetInventory()->GetInventory();
        if (!tmp->empty()) {
            cout << "Items in the location:" << endl;
            for (auto b: *tmp) {
                str += b->getName() + ", ";
            }
            str.pop_back();
            str.pop_back();
            cout << str << endl;
            str = "";
        }

        cout << endl;
    }
}

void WorldGraph::RegisterLocation(Location* loc) {
    _locations.push_back(loc);
}

std::vector<Location*> *WorldGraph::GetLocations() {
    return &_locations;
}

Location* WorldGraph::GetLocationByName(const std::string& name) {
    vector<Location*>::iterator it;

    it = find_if(_locations.begin(), _locations.end(), [&name](Location* obj){return obj->getName() == name;});
    if (it != _locations.end()) {
        return _locations[it - _locations.begin()];
    }
    return nullptr;
}

void WorldGraph::PrintRoomsConnectedToRoom(const string &name) {
    Location* room = GetLocationByName(name);
    cout << "Rooms connected to " << room->getName() << ": " << endl;
    for (const auto& v : _adjList[room->getName()]) {
        cout << "\t> " << v.edge << endl;
    }
}

Location *WorldGraph::GetPlayerLocation() {
    return _playerLocation;
}

void WorldGraph::PrintPlayerDirections() {
    for (const auto& v : _adjList[_playerLocation->getName()]) {
        cout << " > " << v.direction << endl;
    }
}

void WorldGraph::MovePlayerByDirection(const std::string& dir) {
    for (const auto& v : _adjList[_playerLocation->getName()]) {
        if (UtilityFunctions::ToLower(v.direction) == dir){
            _playerLocation->GetInventory()->removeItem(GameManger::Instance()->player());
            _playerLocation = GetLocationByName(v.edge);
            _playerLocation->GetInventory()->addItem(GameManger::Instance()->player());
        }
    }
}

Container *WorldGraph::GetContainerByName(const string& name) {
    Container* container = nullptr;
    for (auto &c : _containers) {
        if (c.getName() == UtilityFunctions::Capitalise(name)) {
            container = &c;
        }
    }
    return container;
}

Item *WorldGraph::GetItemByName(const string& name) {
    Item* item = nullptr;
    for (auto &i : _items) {
        if (i.getName() == name) {
            item = &i;
        }
    }
    return item;
}

Static *WorldGraph::GetStaticByName(const string& name) {
    Static* aStatic = nullptr;
    aStatic = GetItemByName(name);
    if (aStatic == nullptr) {
        aStatic = GetContainerByName(name);
    }
    return aStatic;
}
