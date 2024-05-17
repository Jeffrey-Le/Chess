#include <iostream>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "include/Square.h"
#include "include/Game.h"
#include "include/Board.h"
#include "include/Pawn.h"

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

