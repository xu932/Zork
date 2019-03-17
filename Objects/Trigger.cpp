//
// Created by alex on 3/17/19.
//

#include "../Headers/Trigger.h"

Condition::Condition(rapidxml::xml_node<> *root) : owner(nullptr), object(nullptr) {
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
    object = obj;
}

bool Condition::checkCondition() {
    if (attr.find("has") != attr.end()) {
        if (attr["has"] == "yes" && owner->getObject(attr["object"], ITEM) != nullptr)
            return true;
        else if (attr["has"] == "no" && owner->getObject(attr["object"], ITEM) == nullptr)
            return true;
        return false;
    } else {
        if (object->getInfo("status") == attr["status"])
            return true;
        return false;
    }
}

Trigger::Trigger(rapidxml::xml_node<> *root) : hasTriggered(false), hasInitialized(false) {
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


void Trigger::initTrigger(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                  std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                  std::shared_ptr<GameObject> inventory) {
    hasInitialized = true;
    for (auto i : conditions) {
        i->setObject(items[i->getInfo("object")]);
        auto owner = i->getInfo("owner");
        if (owner == "inventory")
            i->setOwner(inventory);
        else if (owner != "[ERROR]")
            i->setOwner(containers[owner]);
    }
}

bool Trigger::checkTrigger(std::string cmd) {
    if (attr["type"] == "single" && hasTriggered)
        return false;

    bool ret = cmd == attr["command"];
    for (auto i : conditions)
        ret &= i->checkCondition();
    return ret;
}

void Trigger::fire() {
    hasTriggered = true;
    for (auto s : prints)
        std::cout << s << std::endl;
}
