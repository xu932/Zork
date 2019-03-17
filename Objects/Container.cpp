//
// Created by alex on 3/17/19.
//

#include "../Headers/Container.h"

Container::Container() : GameObject(CONTAINER) {}

Container::Container(rapidxml::xml_node<> *root, std::vector<std::string>& items) : GameObject(CONTAINER) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "accept") {
            accepts.insert(std::string(node->value()));
        } else if (name == "trigger") {
            std::shared_ptr<Trigger> trig = std::make_shared<Trigger>(node);
            this->addTrigger(trig);
        } else if (name == "item") {
            items.push_back(std::string(node->value()));
        } else {
            this->addInfo(name, std::string(node->value()));
        }
    }
}

Container::~Container() {}

void Container::initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                             std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                             std::shared_ptr<GameObject> inventory) {
    for (auto i : triggers) {
        if (!(i->hasInitialized))
            i->initTrigger(items, containers, inventory);
    }
}

std::shared_ptr<Trigger> Container::checkTrigger(std::string cmd) {
    for (auto i : triggers) {
        if (i->checkTrigger(cmd))
            return i;
    }

    for (auto i : objects) {
        auto temp = i.second->checkTrigger(cmd);
        if (temp != nullptr)    return temp;
    }

    return nullptr;
}
