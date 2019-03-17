//
// Created by alex on 3/17/19.
//

#ifndef ZORK_MAP_H
#define ZORK_MAP_H

#include "Item.h"
#include "Creature.h"
#include "Container.h"
#include "Room.h"

class Map {
private:
    bool running;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> objects;
public:
    Map(std::unordered_map<std::string, std::vector<rapidxml::xml_node<>*>>& elements);
    virtual ~Map();
};


#endif //ZORK_MAP_H
