#include <iostream>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "include/Square.h"
#include "include/Game.h"
#include "include/Board.h"
#include "include/Pawn.h"
#include "include/Knight.h"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Game test;

    test.openGame();

//    Pawn test2;
//
//    test2.displayBoard();
//
//    Knight test3;
//
//    test3.displayBoard();
//
//    Square *sq = new Square();
//
//    sq->changePiece(1.0f);
//    std::cout << sq->usePiece() << std::endl;
//    sq->setOccupiedPiece(&test2);
//
//    sq->changePiece(3.1f);
//    std::cout << sq->usePiece() << std::endl;
//    sq->setOccupiedPiece(&test3);

    return 0;
}

// set(CMAKE_CXX_STANDARD 20)

