//
// Created by alex on 3/17/19.
//

#ifndef ZORK_ITEM_H
#define ZORK_ITEM_H

#include "Trigger.h"
#include "rapidxml.hpp"

class Item : public GameObject{
private:
    virtual void addTurnOn(rapidxml::xml_node<>* root);

public:
    std::unordered_map<std::string, std::vector<std::string>> turn_on;

    Item(rapidxml::xml_node<>* root);
    virtual ~Item();

    virtual void initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                              std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                              std::shared_ptr<GameObject> inventory);
    virtual void uninitTriggers();
    virtual std::shared_ptr<Trigger> checkTrigger(std::string cmd);

    void turnon();
    virtual void print();
};


#endif //ZORK_ITEM_H
