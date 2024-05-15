//
// Created by Jeffrey Vo Le on 5/10/24.
//


#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>
#include <cstdint>
#include <iomanip>

#include "square.h"
#include "Bitboard.h"

class Board {
    private:
        uint64_t *board;

        Bitboard *bitboard;

        uint64_t fullInt(uint64_t);

        Square *square;


        sf::Font font;

        sf::Text *numPositions;
        sf::Text *letterPositions;
    public:
        Board();
        ~Board();

        void updateBoard(uint64_t*);

        void displayBoard();

        void drawBoard();

        Square *useBoard();

        sf::Text *usePositions(char);
};

#endif //CHESS_BOARD_H
