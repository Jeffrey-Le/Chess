//
// Created by Jeffrey Vo Le on 5/14/24.
//

#ifndef CHESS_BITBOARD_H
#define CHESS_BITBOARD_H

#include <cstdint>

#include "square.h"

class Bitboard {
    private:
        uint64_t board;
        uint64_t convertToBitBoard(std::string);
    public:
        //Bitboard();
        explicit Bitboard(Square *);
        ~Bitboard();

        void displayBitboard();
};

#endif //CHESS_BITBOARD_H
