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

    Pawn test;

    test.displayBoard();

    return 0;

}

// set(CMAKE_CXX_STANDARD 20)

