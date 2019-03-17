//
// Created by alex on 3/17/19.
//

#include "../Headers/Item.h"

void Item::addTurnOn(rapidxml::xml_node<> *root) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (turn_on.find(name) == turn_on.end())
            turn_on[name] = std::vector<std::string>();
        turn_on[name].push_back(std::string(node->value()));
    }
}

Item::Item(rapidxml::xml_node<>* root) : GameObject(ITEM) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "turnon") {
            this->addTurnOn(node);
        } else if (name == "trigger") {
            std::shared_ptr<Trigger> trig = std::make_shared<Trigger>(node);
            this->addTrigger(trig);
        } else {
            this->addInfo(name, std::string(node->value()));
        }
    }
}

void Item::initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                        std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                        std::shared_ptr<GameObject> inventory) {
    for (auto i : triggers) {
        if (!(i->hasInitialized))
            i->initTrigger(items, containers, inventory);
    }
}

Item::~Item() {}


