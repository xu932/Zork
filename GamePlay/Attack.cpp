//
// Created by alex on 3/17/19.
//

#include "../Headers/Attack.h"

Attack::Attack(rapidxml::xml_node<> *root) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "condition") {
            std::unordered_map<std::string, std::string> cond;
            for (auto n = node->first_node(); n; n = n->next_sibling())
                cond[std::string(n->name())] = std::string(n->value());
            conditions.push_back(cond);
        } else if (name == "action") {
            actions.push_back(std::string(node->value()));
        } else if (name == "print") {
            prints.push_back(std::string(node->value()));
        }
    }
}

Attack::~Attack() {}