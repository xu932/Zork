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
public:
    Attack *attack;

    Creature(rapidxml::xml_node<>* root);
    virtual ~Creature();

    virtual void initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                              std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                              std::shared_ptr<GameObject> inventory);
    virtual void uninitTriggers();
    virtual std::shared_ptr<Trigger> checkTrigger(std::string cmd);
    virtual bool attackWith(std::shared_ptr<GameObject> item);

};


#endif //ZORK_CREATURE_H
