//
// Created by alex on 3/17/19.
//

#ifndef ZORK_GAMEOBJECT_H
#define ZORK_GAMEOBJECT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Trigger;

enum Type {
    ITEM,
    CONTAINER,
    CREATURE,
    ROOM
};

class GameObject {
protected:
    std::unordered_map<std::string, std::string> attr;
    std::unordered_map<std::string, std::shared_ptr<GameObject>> objects;
    std::vector<std::shared_ptr<Trigger>> triggers;

public:
    Type type;
    bool deleted;
    GameObject(Type t);
    virtual ~GameObject();

    virtual void addInfo(std::string key, std::string value);
    virtual std::string getInfo(std::string key);

    virtual void addObject(std::shared_ptr<GameObject> obj);
    virtual void deleteObject(std::string key);
    virtual bool hasObject(std::string key);
    virtual std::shared_ptr<GameObject> getObject(std::string key);
    virtual std::shared_ptr<GameObject> getObject(std::string key, Type type);

    virtual void addTrigger(std::shared_ptr<Trigger> trig);
    virtual void initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                              std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                              std::shared_ptr<GameObject> inventory);
    virtual void uninitTriggers();

    virtual std::shared_ptr<Trigger> checkTrigger(std::string cmd);

    virtual void print();
};

#endif //ZORK_GAMEOBJECT_H
