//
// Created by alex on 3/17/19.
//

#include <iostream>
#include <unordered_map>

#include "Headers/rapidxml.hpp"
#include "Headers/rapidxml_utils.hpp"
#include "Headers/Map.h"
#include "Headers/UtilityFunctions.h"

std::unordered_map<std::string, std::vector<rapidxml::xml_node<>*>> extractElements(rapidxml::xml_node<>* root) {
    std::unordered_map<std::string, std::vector<rapidxml::xml_node<>*>> elements;

    for (auto node = root->first_node(); node; node = node->next_sibling()) {
        std::string name(node->name());
        if (elements.find(name) == elements.end()) {
            std::vector<rapidxml::xml_node<>*> temp;
            temp.push_back(node);
            elements[name] = temp;
        } else {
            elements[name].push_back(node);
        }

    }
    return elements;
}

void runZork(Map* map) {
    std::shared_ptr<Container> inventory = std::make_shared<Container>();   // player's inventory
    inventory->addInfo("name", "Player");
    inventory->open = true;

    std::string command;                                                    // for user input command
    std::vector<std::string> parse;                                         // for parsed command
    int type;                                                               // to decode which command it is

    map->initTriggers(inventory);

    std::shared_ptr<Room> current = map->getRoom("Entrance");               // the current room
    current->init();

    while (map->isRunning()) {
        parse.clear();
        command = "";

        // check trigger before do anything
        auto trig = current->checkTrigger("");
        if (trig != nullptr) {
            trig->fire();
            for (auto s : trig->actions)
                map->executeAction(s);
            continue;
        }

        trig = inventory->checkTrigger("");
        if (trig != nullptr) {
            trig->fire();
            for (auto s : trig->actions)
                map->executeAction(s);
            continue;
        }

        // get user input command
        type = 0;
        do {
            std::cout << ">> ";
            std::getline(std::cin, command);
            type = readCommand(command, parse);
            if (type == 0)
                std::cerr << "Error" << std::endl;
        } while (type == 0);

        // check if command triggers any trigger
        trig = current->checkTrigger(command);
        if (trig != nullptr) {
            trig->fire();
            for (auto s : trig->actions)
                map->executeAction(s);
            continue;
        }

        trig = inventory->checkTrigger(command);
        if (trig != nullptr) {
            trig->fire();
            for (auto s : trig->actions)
                map->executeAction(s);
            continue;
        }

        // execute user command
        if (type == 1) {            // n s e w
            std::string next = current->move(direction(parse[0]));
            if (next == "[ERROR]")
                std::cerr << "Can't go that way." << std::endl;
            else {
                current = map->getRoom(next);
                current->init();
            }
        } else if (type == 2) {     // i
            inventory->print();
        } else if (type == 3) {     // take (item)
            auto obj = current->getObject(parse[1]);
            if (obj != nullptr && obj->type == ITEM) {
                current->deleteObject(parse[1]);
                inventory->addObject(obj);
                std::cout << "Item " << obj->getInfo("name") << " added to inventory" << std::endl;
            } else
                std::cerr << "Error" << std::endl;
        } else if (type == 4) {     // open (container)
            auto temp = std::dynamic_pointer_cast<Container>(current->getObject(parse[1]));
            if (temp != nullptr) {
                temp->open = true;
                temp->print2();
            } else
                std::cerr << "No such container" << std::endl;
        } else if (type == 5) {     // open exit
            if (current->getInfo("type") == "exit") {
                map->running = false;
                std::cout << "Game over" << std::endl;
            }
        } else if (type == 6) {     // read (item)
            auto temp = inventory->getObject(parse[1]);
            if (temp != nullptr)
                temp->print();
            else
                std::cerr << "No such item in inventory" << std::endl;
        } else if (type == 7) {     // drop (item)
            auto temp = inventory->getObject(parse[1]);
            if (temp != nullptr) {
                inventory->deleteObject(parse[1]);
                current->addObject(temp);
                std::cerr << temp->getInfo("name") << " dropped" << std::endl;
            } else
                std::cerr << "No such item in inventory" << std::endl;
        } else if (type == 8) {     // put (item) in (container)
            auto item = inventory->getObject(parse[1]);
            auto cont = current->getObject(parse[3]);
            if (item != nullptr && cont != nullptr) {
                inventory->deleteObject(parse[1]);
                cont->addObject(item);
                std::cout << "Item " << item->getInfo("name") << " added to " << cont->getInfo("name") << "." << std::endl;
            } else if (item == nullptr)
                std::cerr << "No such item in inventory" << std::endl;
            else
                std::cerr << "No such container in this room" << std::endl;
        } else if (type == 9) {     // turn on (item)
            auto temp = inventory->getObject(parse[2]);
            if (temp != nullptr) {
                auto item = std::dynamic_pointer_cast<Item>(temp);
                std::cout << "You activated the " << item->getInfo("name") << std::endl;
                item->turnon();
                if (item->turn_on.find("action") != item->turn_on.end()) {
                    for (auto s : item->turn_on["action"])
                        map->executeAction(s);
                }
            } else
                std::cerr << "No such item in inventory" << std::endl;
        } else {                    // attack (creature) with (item)
            auto item = inventory->getObject(parse[3]);
            auto temp = current->getObject(parse[1]);
            if (item != nullptr && temp != nullptr) {
                auto creat = std::dynamic_pointer_cast<Creature>(temp);
                if (creat->attackWith(item)) {
                    for (auto s : (creat->attack)->actions)
                        map->executeAction(s);
                } else
                    std::cerr << "Error: not effective on " << creat->getInfo("name") << std::endl;
            } else if (item == nullptr)
                std::cerr << "No such item in inventory" << std::endl;
            else
                std::cerr << "No such creature in the current room" << std::endl;
        }
    }
    map->uninitTriggers();
}

int main(int argc, char ** argv) {
    rapidxml::file<> xmlFile(argv[1]);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto elements = extractElements(doc.first_node());

    Map *map = new Map(elements);
    runZork(map);

    delete map;
    return EXIT_SUCCESS;
}