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
    CREATURE
};

class GameObject {
private:
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
    virtual std::shared_ptr<GameObject> getObject(std::string key);
    virtual std::shared_ptr<GameObject> getObject(std::string key, Type type);

    virtual void addTrigger(std::shared_ptr<Trigger> trig);
};

#endif //ZORK_GAMEOBJECT_H
