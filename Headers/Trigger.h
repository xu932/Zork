//
// Created by alex on 3/17/19.
//

#ifndef ZORK_TRIGGER_H
#define ZORK_TRIGGER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

#include "rapidxml.hpp"
#include "GameObject.h"

enum DURATION {
    Permanent,
    Single
};

class Trigger {
private:
    std::vector<std::unordered_map<std::string, std::string>> conditions;
    std::unordered_map<std::string, std::string> attr;
public:
    DURATION dur;
    bool hasTriggered;

    std::vector<std::string> actions;
    std::vector<std::string> prints;

    Trigger(rapidxml::xml_node<> *root);
    virtual ~Trigger();

    virtual void fire();

};


#endif //ZORK_TRIGGER_H
