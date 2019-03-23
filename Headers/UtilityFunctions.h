//
// Created by alex on 3/17/19.
//

#ifndef ZORK_UTILITYFUNCTIONS_H
#define ZORK_UTILITYFUNCTIONS_H

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

void parseString(std::string str, std::vector<std::string>& parse);
int readCommand(std::string command, std::vector<std::string>& parse);
int readAction(std::string action, std::vector<std::string>& parse);
std::string direction(std::string dir);
#endif //ZORK_UTILITYFUNCTIONS_H
