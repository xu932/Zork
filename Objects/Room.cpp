//
// Created by alex on 3/17/19.
//

#include "../Headers/Room.h"

void Room::addBorder(rapidxml::xml_node<> *root) {
    std::string dir(root->first_node("direction")->value());
    std::string rm(root->first_node("name")->value());
    borders[dir] = rm;
    n_border++;
}

Room::Room(rapidxml::xml_node<> *root, std::vector<std::string>& everything) : GameObject(ROOM), n_border(0) {

    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "item" || name == "container" || name == "creature") {
            everything.push_back(std::string(node->value()));
        } else if (name == "trigger") {
            std::shared_ptr<Trigger> trig = std::make_shared<Trigger>(node);
            this->addTrigger(trig);
        } else if (name == "border") {
            this->addBorder(node);
        } else {
            this->addInfo(name, std::string(node->value()));
        }
    }
}

Room::~Room() {}