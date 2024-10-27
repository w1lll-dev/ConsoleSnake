#ifndef GAME_HPP
#define GAME_HPP

#include <cstdint>
#include <random>

struct Border {
    const uint8_t width, height;
};

struct Snake {
    uint8_t x, y;
    uint8_t tailX[100], tailY[100];
    uint16_t tailLength;
};

struct Fruit {
    uint8_t x, y;
};

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Game {
public:
    Game(const Border& border);

    void Draw();
    void HandleInput();
    void Logic();

    bool gameOver = false;

private:
    void RandomizeFruitPos();

    Snake snake;
    Fruit fruit;
    Direction dir = RIGHT;
    uint16_t score = 0;

    std::random_device rd;

    const Border border;
};

#endif