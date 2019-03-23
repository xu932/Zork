//
// Created by alex on 3/17/19.
//

#include "../Headers/Room.h"

void Room::addBorder(rapidxml::xml_node<> *root) {
    std::string dir(root->first_node("direction")->value());
    std::string rm(root->first_node("name")->value());
    borders[dir] = rm;
}

Room::Room(rapidxml::xml_node<> *root, std::unordered_map<std::string, std::vector<std::string>>& everything) : GameObject(ROOM) {
    everything["item"] = std::vector<std::string>();
    everything["creature"] = std::vector<std::string>();
    everything["container"] = std::vector<std::string>();
    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (name == "item" || name == "container" || name == "creature") {
            everything[name].push_back(std::string(node->value()));
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

void Room::initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                        std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                        std::shared_ptr<GameObject> inventory) {
    for (auto i : triggers) {
        if (!(i->hasInitialized))
            i->initTrigger(items, containers, inventory);
    }
}

void Room::uninitTriggers() {
    for (auto i : triggers) {
        if (i->hasInitialized)
            i->uninitTrigger();
    }
}

std::shared_ptr<GameObject> Room::getObject(std::string key) {
    if (objects.find(key) != objects.end()) {
        auto ret = objects[key];
        return ret;
    } else {
        for (auto i : objects) {
            if (i.second->type == CONTAINER) {
                auto ret = i.second->getObject(key);
                if (ret != nullptr) {
                    i.second->deleteObject(key);
                    return ret;
                }
            }
        }
        return nullptr;
    }
}

void Room::init() {
    std::string description = this->getInfo("description");
    std::cout << description << std::endl;
}

std::shared_ptr<Trigger> Room::checkTrigger(std::string cmd) {
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

void Room::deleteBorder(std::string room) {
    for (auto i : borders) {
        if (i.second == room)
            borders.erase(i.first);
    }
}

std::string Room::move(std::string direction) {
    if (borders.find(direction) != borders.end())
        return borders[direction];
    return "[ERROR]";
}


