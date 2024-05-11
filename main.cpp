#include <iostream>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "include/square.h"
#include "include/game.h"
#include "include/board.h"
#include "include/pawn.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Game test;

    test.openGame();

    Pawn test2;

    test2.displayBoard();

    return 0;

}

// set(CMAKE_CXX_STANDARD 20)

