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
    Container(rapidxml::xml_node<>* root, std::vector<std::string>& items);
    ~Container();
};


#endif //ZORK_CONTAINER_H
