//
// Created by alex on 3/17/19.
//

#ifndef ZORK_CREATURE_H
#define ZORK_CREATURE_H

#include <unordered_set>

#include "Trigger.h"
#include "Attack.h"
#include "rapidxml.hpp"


class Creature : public GameObject {
private:
    std::unordered_set<std::string> vulner;
    Attack *attack;
public:
    Creature(rapidxml::xml_node<>* root);
    virtual ~Creature();

    virtual void initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                              std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                              std::shared_ptr<GameObject> inventory);

};


#endif //ZORK_CREATURE_H
