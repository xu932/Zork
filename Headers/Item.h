//
// Created by alex on 3/17/19.
//

#ifndef ZORK_ITEM_H
#define ZORK_ITEM_H

#include "GameObject.h"
#include "rapidxml.hpp"

class Item : public GameObject{
private:
    std::unordered_map<std::string, std::vector<std::string>> turn_on;

public:
    Item();
    virtual ~Item();

    virtual void addTurnOn(rapidxml::xml_node<>* root);
    void turnon();
};


#endif //ZORK_ITEM_H
