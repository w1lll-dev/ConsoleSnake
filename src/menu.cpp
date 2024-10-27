#include <iostream>
#include <cstdint>

#include "menu.hpp"

Menu::Menu() {
    
}

void Menu::Draw() {
    std::cout << selectString << '\n';
    std::string end = "\033[0m";
    std::string color;

    for (auto& diffString : diffStrings) {
        std::string spaces;

        

        for (uint8_t i = 0; i < (selectString.size() / 2) - (diffString.size() / 2); ++i) {
            spaces += ' ';
        }
        std::cout << spaces << diffString << '\n';
    }
}