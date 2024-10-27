#include <iostream>

#include "game.hpp"
#include "input.hpp"

Game::Game(const Border& border) : border(border) {
    snake.x = border.width / 2;
    snake.y = border.height / 2;
    snake.tailLength = 2;

    RandomizeFruitPos();
}

void Game::Draw() {
    // Clear console
    system("clear");

    std::string snakeHead = "\033[1;32mO \033[0m";
    std::string snakeTail = "\033[1;32mo \033[0m";

    if (gameOver) {
        snakeHead = "\033[1;31mO \033[0m";
        snakeTail = "\033[1;31mo \033[0m";
    }

    // Loop through border height and width
    for (uint8_t y = 0; y < border.height; ++y) {
        for (uint8_t x = 0; x < border.width; ++x) {

            // If y is at the top or bottom of the border, draw square
            if (y == 0 || y == border.height - 1)
                std::cout << "\033[1;37m⎯ \033[0m";

            // If x is at the start or end of the border, draw square
            else if (x == 0 || x == border.width - 1)
                std::cout << "\033[1;37m│ \033[0m";

            // Draw snake head
            else if (y == snake.y && x == snake.x)
                std::cout << snakeHead;

            // Draw fruit
            else if (y == fruit.y && x == fruit.x)
                std::cout << "\033[1;31mO \033[0m";

            // Draw tail or space
            else {
                bool printTail = false;

                for (uint16_t i = 0; i < snake.tailLength; ++i) {
                    if (x == snake.tailX[i] && y == snake.tailY[i]) {
                        std::cout << snakeTail;
                        printTail = true;
                    }
                }

                if (!printTail)
                    std::cout << "  ";
            }
        }
        std::cout << '\n';
    }

    // Show score
    std::cout << "Score: " << score << '\n';

    // Game over
    if (gameOver)
        std::cout << "GAME OVER!" << '\n';
}

void Game::HandleInput() {
    switch (Input::GetKey()) {
    case 'a':
        if (dir != RIGHT)
            dir = LEFT;
        break;
    case 'd':
        if (dir != LEFT)
            dir = RIGHT;
        break;
    case 'w':
        if (dir != DOWN)
            dir = UP;
        break;
    case 's':
        if (dir != UP)
            dir = DOWN;
        break;
    case 'x':
        gameOver = true;
        break;
    }
}

void Game::Logic() {
    uint8_t prevX = snake.tailX[0];
    uint8_t prevY = snake.tailY[0];
    uint8_t prev2X, prev2Y;

    snake.tailX[0] = snake.x;
    snake.tailY[0] = snake.y;
    
    for (uint16_t i = 1; i < snake.tailLength; ++i) {
        prev2X = snake.tailX[i];
        prev2Y = snake.tailY[i];

        snake.tailX[i] = prevX;
        snake.tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        snake.x--;
        break;
    case RIGHT:
        snake.x++;
        break;
    case UP:
        snake.y--;
        break;
    case DOWN:
        snake.y++;
        break;
    }

    if (snake.x > border.width - 2 || snake.x < 1 || snake.y > border.height - 2 || snake.y < 1) {
        std::cout << "\a"; // Sound

        gameOver = true;
    }

    for (uint16_t i = 0; i < snake.tailLength; ++i) {
        if (snake.tailX[i] == snake.x && snake.tailY[i] == snake.y) {
            std::cout << "\a"; // Sound

            gameOver = true;
        }
    }

    if (snake.x == fruit.x && snake.y == fruit.y) {
        std::cout << "\a"; // Sound

        score++;
        snake.tailLength++;

        RandomizeFruitPos();
    }
}

void Game::RandomizeFruitPos() {
    // Initialize valid spawn coords
    std::vector<uint16_t> validX, validY;

    for (uint8_t x = 1; x < border.width - 2; ++x)
        validX.push_back(x);
    for (uint8_t y = 1; y < border.height - 2; ++y)
        validY.push_back(y);

    // Exclude snake head so fruit won't spawn on it
    validX.erase(std::remove(validX.begin(), validX.end(), snake.x), validX.end());
    validY.erase(std::remove(validY.begin(), validY.end(), snake.y), validY.end());

    // Exclude snake tail so fruit won't spawn on it
    for (uint16_t i = 1; i < snake.tailLength; ++i) {
        validX.erase(std::remove(validX.begin(), validX.end(), snake.tailX[i]), validX.end());
        validY.erase(std::remove(validY.begin(), validY.end(), snake.tailY[i]), validY.end());
    }

    // Shuffle valid coords list
    std::shuffle(validX.begin(), validX.end(), rd);
    std::shuffle(validY.begin(), validY.end(), rd);

    uint16_t randomX = validX.front();
    uint16_t randomY = validY.front();

    fruit.x = randomX;
    fruit.y = randomY;
}