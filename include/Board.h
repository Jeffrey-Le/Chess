//
// Created by Jeffrey Vo Le on 5/10/24.
//


#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>
#include <cstdint>
#include <iomanip>

#include "Square.h"
#include "Bitboard.h"

class Board {
    private:
        Bitboard *board;

        static uint64_t fullInt(uint64_t);

        Square *square;


        sf::Font font;

        sf::Text *numPositions;
        sf::Text *letterPositions;
    public:
        Board();
        ~Board();

        void updateBoard(Bitboard *);

        void setSquares(Square *);

        void displayBoard() const;

        void startGame() const;

        void drawBoard() const;

        Square *useBoard() const;

        sf::Text *usePositions(char) const;
};

#endif //CHESS_BOARD_H
