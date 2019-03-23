//
// Created by alex on 3/17/19.
//

#ifndef ZORK_CONTAINER_H
#define ZORK_CONTAINER_H

#include <unordered_set>

#include "Trigger.h"
#include "rapidxml.hpp"

class Container : public GameObject {
private:
    std::unordered_set<std::string> accepts;
public:
    bool open;

    Container();
    Container(rapidxml::xml_node<>* root, std::vector<std::string>& items);
    virtual ~Container();

    virtual void initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                              std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                              std::shared_ptr<GameObject> inventory);
    virtual void uninitTriggers();
    virtual std::shared_ptr<GameObject> getObject(std::string key);
    virtual std::shared_ptr<Trigger> checkTrigger(std::string cmd);
    virtual void print();

    virtual void print2();

};


#endif //ZORK_CONTAINER_H
