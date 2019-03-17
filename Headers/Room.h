//
// Created by alex on 3/17/19.
//

#ifndef ZORK_ROOM_H
#define ZORK_ROOM_H

#include "Trigger.h"
#include "rapidxml.hpp"

class Room : public GameObject {
private:
    int n_border;
    std::unordered_map<std::string, std::string> borders;

    void addBorder(rapidxml::xml_node<>* root);
public:
    Room(rapidxml::xml_node<>* root, std::unordered_map<std::string, std::vector<std::string>>& everything);
    virtual ~Room();
};


#endif //ZORK_ROOM_H
