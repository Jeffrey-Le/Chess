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
        explicit Bitboard(Square *);
        ~Bitboard();

        // Possible Moves
        void pawnMoves(float);
        void knightMoves(float);
        void bishopMoves(float);
        void rookMoves(float);
        void queenMoves(float);
        void kingMoves(float);

        static uint64_t convertToBitBoard(std::string const &);
        void updateBitboard(std::string const &);
        void displayBitboard() const;

        uint64_t useBitboard() const;
};

#endif //CHESS_BITBOARD_H
