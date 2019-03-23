//
// Created by alex on 3/17/19.
//
#include "../Headers/UtilityFunctions.h"

void parseString(std::string str, std::vector<std::string>& parse) {
    int prev = 0;
    parse.clear();
    for (unsigned int i = 1; i < str.length(); i++) {
        if (str[i] != ' ')  continue;
        parse.push_back(str.substr(prev, i - prev));
        prev = i + 1;
    }
    parse.push_back(str.substr(prev));
}

int readCommand(std::string command, std::vector<std::string>& parse) {
    parseString(command, parse);
    int size = parse.size();

    if (parse[0] == "n" || parse[0] == "s" || parse[0] == "e" || parse[0] == "w")   return 1;
    else if (parse[0] == "i" || parse[0] == "inventory")                            return 2;
    else if (parse[0] == "take")                                                    return 3;
    else if (parse[0] == "open") {
        if (size >= 2 && parse[1] != "exit")                                        return 4;
        else if (size >= 2)                                                         return 5;
        else return 0;
    } else if (parse[0] == "read" && size >= 2)                                     return 6;
    else if (parse[0] == "drop" && size >= 2)                                       return 7;
    else if (parse[0] == "put") {
        for (int i = 1; i < size - 1; i++) {
            if (parse[i] == "in")                                                   return 8;
        }
        return 0;
    } else if (parse[0] == "turn" && size >= 3 && parse[1] == "on")                 return 9;
    else if (parse[0] == "attack") {
        for (int i = 1; i < size - 1; i++) {
            if (parse[i] == "with")                                                 return 10;
        }
        return 0;
    } else
        return 0;
}

int readAction(std::string action, std::vector<std::string>& parse) {
    parseString(action, parse);
    int size = parse.size();
    if (size == 4 && parse[0] == "Add" && parse[2] == "to")
        return 1;
    else if (size == 2 && parse[0] == "Delete")
        return 2;
    else if (size == 4 && parse[0] == "Update" && parse[2] == "to")
        return 3;
    else if (action == "Game Over")
        return 4;
    return 0;
}

std::string direction(std::string dir) {
    if (dir == "n")         return "north";
    else if (dir == "s")    return "south";
    else if (dir == "w")    return "west";
    else                    return "east";
}
