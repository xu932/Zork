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

void GameObject::addObject(std::shared_ptr<GameObject> obj) {
    obj->deleted = false;
    std::string name = obj->getInfo("name");
    objects[name] = obj;
}

void GameObject::deleteObject(std::string key) {
    objects.erase(key);
}

bool GameObject::hasObject(std::string key) {
    return objects.find(key) != objects.end();
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

void GameObject::initTriggers(std::unordered_map<std::string, std::shared_ptr<GameObject>>& items,
                          std::unordered_map<std::string, std::shared_ptr<GameObject>>& containers,
                          std::shared_ptr<GameObject> inventory) {
    return;
}

void GameObject::uninitTriggers() {}

std::shared_ptr<Trigger> GameObject::checkTrigger(std::string cmd) {
    return nullptr;
}

void GameObject::print() {
    std::cout << type << " " << attr["name"] << std::endl;
}