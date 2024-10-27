#include <termios.h>
#include <unistd.h>
#include <iostream>

#include "input.hpp"

char Input::GetKey() {
    struct termios oldt, newt;
    char ch;

    tcgetattr(STDIN_FILENO, &oldt);  // Get the current terminal settings
    newt = oldt;                       // Copy them to newt
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings
    ch = getchar();                   // Read a single character
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old settings
    return ch;
}