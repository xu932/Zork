//
// Created by alex on 3/17/19.
//

#include "../Headers/Map.h"

std::shared_ptr<GameObject> Map::getObject(std::string key) {
    if (objects[ITEM].find(key) != objects[ITEM].end())
        return objects[ITEM][key];
    if (objects[CREATURE].find(key) != objects[CREATURE].end())
        return objects[CREATURE][key];
    if (objects[CONTAINER].find(key) != objects[CONTAINER].end())
        return objects[CONTAINER][key];
    if (objects[ROOM].find(key) != objects[ROOM].end())
        return objects[ROOM][key];

    return nullptr;
}

Map::Map(std::unordered_map<std::string, std::vector<rapidxml::xml_node<>*>>& elements) : running(true) {
    std::shared_ptr<GameObject> temp;
    objects[ITEM] = std::unordered_map<std::string, std::shared_ptr<GameObject>>();
    objects[CONTAINER] = std::unordered_map<std::string, std::shared_ptr<GameObject>>();
    objects[CREATURE] = std::unordered_map<std::string, std::shared_ptr<GameObject>>();
    objects[ROOM] = std::unordered_map<std::string, std::shared_ptr<GameObject>>();
    for (auto i : elements["item"]) {
        std::shared_ptr<Item> item = std::make_shared<Item>(i);
        temp = std::dynamic_pointer_cast<GameObject>(item);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]") {
            objects[ITEM][key] = temp;
            megaObjects[key] = temp;
        }
    }

    for (auto i : elements["creature"]) {
        std::shared_ptr<Creature> creature = std::make_shared<Creature>(i);
        temp = std::dynamic_pointer_cast<GameObject>(creature);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]") {
            objects[CREATURE][key] = temp;
            megaObjects[key] = temp;
        }
    }

    for (auto i : elements["container"]) {
        std::vector<std::string> items;
        std::shared_ptr<Container> cont = std::make_shared<Container>(i, items);
        for (auto j : items)
            cont->addObject(objects[ITEM][j]);
        temp = std::dynamic_pointer_cast<GameObject>(cont);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]") {
            objects[CONTAINER][key] = temp;
            megaObjects[key] = temp;
        }
    }

    for (auto i : elements["room"]) {
        std::unordered_map<std::string, std::vector<std::string>> everything;
        std::shared_ptr<Room> room = std::make_shared<Room>(i, everything);

        for (auto j : everything["item"])
            room->addObject(objects[ITEM][j]);
        for (auto j : everything["creature"])
            room->addObject(objects[CREATURE][j]);
        for (auto j : everything["container"])
            room->addObject(objects[CONTAINER][j]);

        temp = std::dynamic_pointer_cast<GameObject>(room);
        std::string key = temp->getInfo("name");
        if (key != "[ERROR]") {
            objects[ROOM][key] = temp;
            megaObjects[key] = temp;
        }
    }
}

Map::~Map() {}

bool Map::isRunning() {
    return running;
}

std::shared_ptr<Item> Map::getItem(std::string key) {
    auto temp = this->getObject(key);
    if (temp == nullptr || temp->type != ITEM)
        return nullptr;
    return std::dynamic_pointer_cast<Item>(temp);
}

std::shared_ptr<Container> Map::getContainer(std::string key) {
    auto temp = this->getObject(key);
    if (temp == nullptr || temp->type != CONTAINER)
        return nullptr;
    return std::dynamic_pointer_cast<Container>(temp);
}

std::shared_ptr<Creature> Map::getCreature(std::string key) {
    auto temp = this->getObject(key);
    if (temp == nullptr || temp->type != CREATURE)
        return nullptr;
    return std::dynamic_pointer_cast<Creature>(temp);
}

std::shared_ptr<Room> Map::getRoom(std::string key) {
    auto temp = this->getObject(key);
    if (temp == nullptr || temp->type != ROOM)
        return nullptr;
    return std::dynamic_pointer_cast<Room>(temp);
}

void Map::initTriggers(std::shared_ptr<Container> inventory) {
    auto temp = std::dynamic_pointer_cast<GameObject>(inventory);
    for (auto i : megaObjects)
        i.second->initTriggers(objects[ITEM], objects[CONTAINER], temp);
}

void Map::uninitTriggers() {
    for (auto i : megaObjects)
        i.second->uninitTriggers();
}

std::shared_ptr<Room> Map::executeAction(std::string action, std::shared_ptr<Container> inventory, std::shared_ptr<Room> current) {
    std::vector<std::string> parse;
    int type = readAction(action, parse);
    if (type == 1) {
        megaObjects[parse[3]]->addObject(megaObjects[parse[1]]);
    } else if (type == 2) {
        if (megaObjects[parse[1]]->type == ROOM) {
            std::shared_ptr<Room> temp;
            for (auto i : objects[ROOM]) {
                temp = std::dynamic_pointer_cast<Room>(i.second);
                temp->deleteBorder(parse[1]);
            }
        } else {
            megaObjects[parse[1]]->deleted = true;
            for (auto i : megaObjects) {
                if (i.second->getObject(parse[1]) != nullptr)
                    i.second->deleteObject(parse[1]);
            }
        }
    } else if (type == 3) {
        megaObjects[parse[1]]->addInfo("status", parse[3]);
    } else if (type == 4) {
        std::cout << "Victory" << std::endl;
        running = false;
    } else if (type == 0) {
        type = readCommand(action, parse);
        if (type == 1) {            // n s e w
            std::string next = current->move(direction(parse[0]));
            if (next == "[ERROR]")
                std::cerr << "Can't go that way." << std::endl;
            else {
                current = this->getRoom(next);
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
                this->running = false;
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
                        current = this->executeAction(s, inventory, current);
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
                        current = this->executeAction(s, inventory, current);
                } else
                    std::cerr << "Error: not effective on " << creat->getInfo("name") << std::endl;
            } else if (item == nullptr)
                std::cerr << "No such item in inventory" << std::endl;
            else
                std::cerr << "No such creature in the current room" << std::endl;
        }
    }
    return current;
}

void Map::print() {
    for (auto i : objects[ITEM]) {
        std::cout << i.first << " " << i.second << " " << i.second->getInfo("name") << std::endl;
    }
    for (auto i : objects[CREATURE]) {
        std::cout << i.first << " " << i.second << " " << i.second->getInfo("name") << std::endl;
    }
    for (auto i : objects[CONTAINER]) {
        std::cout << i.first << " " << i.second << " " << i.second->getInfo("name") << std::endl;
    }
    for (auto i : objects[ROOM]) {
        std::cout << i.first << " " << i.second << " " << i.second->getInfo("name") << std::endl;
    }
}