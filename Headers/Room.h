//
// Created by alex on 3/17/19.
//

#ifndef ZORK_ROOM_H
#define ZORK_ROOM_H

#include "Trigger.h"
#include "Item.h"
#include "Container.h"
#include "rapidxml.hpp"

class Room : public GameObject {
private:
    std::unordered_map<std::string, std::string> borders;

    void addBorder(rapidxml::xml_node<>* root);
public:
    Room(rapidxml::xml_node<>* root, std::unordered_map<std::string, std::vector<std::string>>& everything);
    virtual ~Room();

    virtual void initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                              std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                              std::shared_ptr<GameObject> inventory);
    virtual void uninitTriggers();

    virtual std::shared_ptr<GameObject> getObject(std::string key);

    void init();
    virtual std::shared_ptr<Trigger> checkTrigger(std::string cmd);
    virtual void deleteBorder(std::string room);
    virtual std::string move(std::string direction);
};


#endif //ZORK_ROOM_H
