#include<iostream>
#include<sstream>
#include "./utils.h"

std::vector<std::string> util::split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string number;
        while (std::getline(ss, number, delim)) {
            elems.push_back(number);
        }
        return elems;
}