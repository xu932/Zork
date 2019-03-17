//
// Created by alex on 3/17/19.
//

#include "../Headers/Map.h"

Map::Map(std::unordered_map<std::string, std::vector<rapidxml::xml_node<>*>>& elements) : running(true) {
    std::shared_ptr<GameObject> temp;

    for (auto i : elements["item"]) {
        std::shared_ptr<Item> item = std::make_shared<Item>(i);
        temp = std::dynamic_pointer_cast<GameObject>(item);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]")  objects[key] = temp;
    }

    for (auto i : elements["creature"]) {
        std::shared_ptr<Creature> creature = std::make_shared<Creature>(i);
        temp = std::dynamic_pointer_cast<GameObject>(creature);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]")  objects[key] = temp;
    }

    for (auto i : elements["container"]) {
        std::vector<std::string> items;
        std::shared_ptr<Container> cont = std::make_shared<Container>(i, items);
        for (auto j : items)
            cont->addObject(objects[j]);
        temp = std::dynamic_pointer_cast<GameObject>(cont);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]")  objects[key] = temp;
    }

    for (auto i : elements["room"]) {
        std::vector<std::string> everything;
        std::shared_ptr<Room> room = std::make_shared<Room>(i, everything);
        for (auto j : everything)
            room->addObject(objects[j]);
        temp = std::dynamic_pointer_cast<GameObject>(room);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]")   objects[key] = temp;
    }
}

Map::~Map() {}
