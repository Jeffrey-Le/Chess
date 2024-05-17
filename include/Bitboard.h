//
// Created by Jeffrey Vo Le on 5/14/24.
//

#ifndef CHESS_BITBOARD_H
#define CHESS_BITBOARD_H

#include <cstdint>

#include "Square.h"

class Bitboard {
    private:
        uint64_t board;
    public:
        Bitboard();
        Bitboard(Square *);
        ~Bitboard();

        uint64_t convertToBitBoard(std::string);
        void updateBitboard(std::string);
        void displayBitboard();

        uint64_t useBitboard();
};

#endif //CHESS_BITBOARD_H
