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
                current = map->executeAction(s, inventory, current);
            continue;
        }

        trig = inventory->checkTrigger("");
        if (trig != nullptr) {
            trig->fire();
            for (auto s : trig->actions)
                current = map->executeAction(s, inventory, current);
            continue;
        }

        // get user input command
        type = 0;
        do {
            //std::cout << ">> ";
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
                current = map->executeAction(s, inventory, current);
            continue;
        }

        trig = inventory->checkTrigger(command);
        if (trig != nullptr) {
            trig->fire();
            for (auto s : trig->actions)
                current = map->executeAction(s, inventory, current);
            continue;
        }

        current = map->executeAction(command, inventory, current);
        
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
