//
// Created by alex on 3/17/19.
//

#ifndef ZORK_ATTACK_H
#define ZORK_ATTACK_H

#include <vector>
#include <unordered_map>
#include <string>

#include "rapidxml.hpp"

class Attack {
public:
    std::vector<std::unordered_map<std::string, std::string>> conditions;
    std::vector<std::string> prints;
    std::vector<std::string> actions;
    Attack(rapidxml::xml_node<>* root);
    virtual ~Attack();
};


#endif //ZORK_ATTACK_H
