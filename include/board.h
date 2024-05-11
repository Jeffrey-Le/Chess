//
// Created by Jeffrey Vo Le on 5/10/24.
//


#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>
#include <cstdint>
#include <iomanip>

class Board {
    private:
        uint64_t *board;

        uint64_t fullInt(uint64_t);
    public:
        Board();

        void updateBoard(uint64_t*);

        void displayBoard();
};

#endif //CHESS_BOARD_H
