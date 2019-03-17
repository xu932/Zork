//
// Created by alex on 3/17/19.
//

#include "../Headers/Trigger.h"

Condition::Condition(rapidxml::xml_node<> *root) : initialzed(false), owner(nullptr), object(nullptr) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        attr[std::string(node->name())] = std::string(node->value());
    }
}

Condition::~Condition() {}

std::string Condition::getInfo(std::string key) {
    if (attr.find(key) == attr.end())
        return "[ERROR]";
    return attr[key];
}

void Condition::setOwner(std::shared_ptr<GameObject> own) {
    owner = own;
}

void Condition::setObject(std::shared_ptr<GameObject> obj) {
    initialzed = true;
    object = obj;
}

bool Condition::checkConiditon() {
    return false;
}

Trigger::Trigger(rapidxml::xml_node<> *root) : hasTriggered(false) {
    attr["type"] = "single";
    attr["command"] = "";
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "condition") {
            std::shared_ptr<Condition> cond = std::make_shared<Condition>(node);
            conditions.push_back(cond);
        } else if (name == "action") {
            actions.push_back(std::string(node->value()));
        } else if (name == "print") {
            prints.push_back(std::string(node->value()));
        } else {
            attr[name] = std::string(node->value());
        }
    }
}

Trigger::~Trigger() {}

void Trigger::fire() {

}
