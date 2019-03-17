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

class Condition {
private:
    bool initialzed;
    std::unordered_map<std::string, std::string> attr;
    std::shared_ptr<GameObject> owner;
    std::shared_ptr<GameObject> object;
public:
    Condition(rapidxml::xml_node<>* root);
    virtual ~Condition();

    void setOwner(std::shared_ptr<GameObject> own);
    void setObject(std::shared_ptr<GameObject> obj);
    std::string getInfo(std::string key);
    bool checkConiditon();
};



class Trigger {
private:
    std::vector<std::shared_ptr<Condition>> conditions;
    std::unordered_map<std::string, std::string> attr;
public:
    bool hasTriggered;

    std::vector<std::string> actions;
    std::vector<std::string> prints;

    Trigger(rapidxml::xml_node<> *root);
    virtual ~Trigger();

    virtual void fire();

};


#endif //ZORK_TRIGGER_H
