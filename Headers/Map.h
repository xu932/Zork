//
// Created by alex on 3/17/19.
//

#ifndef ZORK_MAP_H
#define ZORK_MAP_H

#include "Item.h"
#include "Creature.h"
#include "Container.h"
#include "Room.h"
#include "UtilityFunctions.h"

class Map {
private:
    std::unordered_map<Type, std::unordered_map<std::string, std::shared_ptr<GameObject>>> objects;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> megaObjects;
    std::shared_ptr<GameObject> getObject(std::string key);
public:
    bool running;
    Map(std::unordered_map<std::string, std::vector<rapidxml::xml_node<>*>>& elements);
    virtual ~Map();

    bool isRunning();

    std::shared_ptr<Item> getItem(std::string key);
    std::shared_ptr<Container> getContainer(std::string key);
    std::shared_ptr<Creature> getCreature(std::string key);
    std::shared_ptr<Room> getRoom(std::string key);

    void initTriggers(std::shared_ptr<Container> inventory);
    void uninitTriggers();

    void executeAction(std::string action);

    void print();
};


#endif //ZORK_MAP_H
