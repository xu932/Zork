//
// Created by alex on 3/17/19.
//

#include "../Headers/GameObject.h"

GameObject::GameObject(Type t) : type(t), deleted(false) {}

GameObject::~GameObject() {}

void GameObject::addInfo(std::string key, std::string value) {
    attr[key] = value;
}

std::string GameObject::getInfo(std::string key) {
    if (attr.find(key) != attr.end())
        return attr[key];
    return "[ERROR]";
}

void GameObject::addObject(std::shared_ptr <GameObject> obj) {
    std::string name = obj->getInfo("name");
    objects[name] = obj;
}

std::shared_ptr<GameObject> GameObject::getObject(std::string key) {
    if (objects.find(key) != objects.end())
        return objects[key];
    return nullptr;
}


std::shared_ptr<GameObject> GameObject::getObject(std::string key, Type type) {
    auto ret = this->getObject(key);
    if (ret != nullptr && ret->type == type)
        return ret;
    return nullptr;
}

void GameObject::addTrigger(std::shared_ptr <Trigger> trig) {
    triggers.push_back(trig);
}
