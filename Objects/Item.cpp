//
// Created by alex on 3/17/19.
//

#include "../Headers/Item.h"

Item::Item() : GameObject(ITEM) {}

Item::~Item() {}

void Item::addTurnOn(rapidxml::xml_node<> *root) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (turn_on.find(name) == turn_on.end())
            turn_on[name] = std::vector<std::string>();
        turn_on[name].push_back(std::string(node->value()));
    }
}


