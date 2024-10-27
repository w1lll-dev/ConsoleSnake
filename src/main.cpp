#include <thread>

#include "menu.hpp"
#include "game.hpp"

using namespace std::literals::chrono_literals;

// Constantly called
void InputThread(Game& game) {
    while (!game.gameOver) {
        game.HandleInput();
    }
}

// Called every 100 milliseconds
void LogicThread(Game& game) {
    while (!game.gameOver) {
        game.Logic();
        game.Draw();
        std::this_thread::sleep_for(100ms);
    }
}

int main() {
    Menu menu;

    menu.Draw();

    /*Border border = { 20, 20 };

    Game game(border);

    std::thread input(InputThread, std::ref(game));
    std::thread logic(LogicThread, std::ref(game));

    logic.join(); // Wait for logic thread to end before closing game
    input.detach(); // Don't wait for input thread to end before closing game

    return 0;*/
}