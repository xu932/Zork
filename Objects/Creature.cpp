//
// Created by alex on 3/17/19.
//

#include "../Headers/Creature.h"

Creature::Creature(rapidxml::xml_node<>* root) : GameObject(CREATURE), attack(nullptr) {
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "vulnerability") {
            vulner.insert(std::string(node->value()));
        } else if (name == "attack") {
            attack = new Attack(node);
        } else if (name == "trigger") {
            std::shared_ptr<Trigger> trig = std::make_shared<Trigger>(node);
            this->addTrigger(trig);
        } else {
            this->addInfo(name, std::string(node->value()));
        }
    }
}

Creature::~Creature() {
    if (attack != nullptr)
        delete attack;
}

void Creature::initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                        std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                        std::shared_ptr<GameObject> inventory) {
    for (auto i : triggers) {
        if (!(i->hasInitialized))
            i->initTrigger(items, containers, inventory);
    }
}

std::shared_ptr<Trigger> Creature::checkTrigger(std::string cmd) {
    for (auto i : triggers) {
        if (i->checkTrigger(cmd))
            return i;
    }
    return nullptr;
}

