//
// Created by alex on 3/17/19.
//

#include "../Headers/Trigger.h"

Trigger::Trigger(rapidxml::xml_node<> *root) : dur(Single), hasTriggered(false) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "type") {
            if (std::string(node->value()) == "permanent")
                dur = Permanent;
        } else if (name == "condition") {
            std::unordered_map<std::string, std::string> cond;
            for (auto n = node->first_node(); n; n = n->next_sibling())
                cond[std::string(n->name())] = std::string(n->value());
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
