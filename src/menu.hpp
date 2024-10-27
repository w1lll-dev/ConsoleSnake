#ifndef MENU_HPP
#define MENU_HPP

#include <string>

enum Difficulty {
    BABY,
    EASY,
    MEDIUM,
    HARD,
    IMPOSSIBLE
};

class Menu {
public: 
    Menu();

    void Draw();

private:
    Difficulty diff;

    std::string selectString = ">---- SELECT DIFFICULTY ----<";
    std::string diffStrings[5] = { "BABY", "EASY", "MEDIUM", "HARD", "IMPOSSIBLE" };
};

#endif