//
// Created by Crolw on 5/31/2024.
//


#ifndef MOVES_H
#define MOVES_H

#include <cstdint>

#include "Bitboard.h"

class Moves {
    private:
        uint64_t FILE_A = 9259542123273814144UL; // 0x0101010101010101
        uint64_t FILE_H = 72340172838076673ULL; // 0x8080808080808080
        uint64_t FILE_AB = 13889313184910721216ULL; // 0xc0c0c0c0c0c0c0c0
        uint64_t FILE_GH = 217020518514230019ULL; // 0x0303030303030303
        uint64_t RANK_1 = 18374686479671623680ULL; // 0xff00000000000000
        uint64_t RANK_4 = 1095216660480; // 0x000000ff00000000
        uint64_t RANK_5 = 4278190080ULL; // 0x00000000ff000000
        uint64_t RANK_8 = 255ULL; // 0x00000000000000ff
        uint64_t CENTRE = 103481868288ULL; // 0x0000001818000000
        uint64_t EXTENDED_CENTRE = 1125899906580480ULL; // 0x00003fffffffc0000
        uint64_t KING_SIDE = 1085102592571150095ULL; // 0x0f0f0f0f0f0f0f0f
        uint64_t QUEEN_SIDE = 17361641481138401520ULL; // 0xf0f0f0f0f0f0f0f0
        uint64_t KING_B7 = 512ull;//18014398509481984ULL; // 0x0040000000000000
        uint64_t KNIGHT_C6 = 262144ull;//35184372088832ULL; // 0x0000200000000000
        uint64_t NOT_WHITE_PIECES = 0ULL;
        uint64_t BLACK_PIECES = 0ULL;
        uint64_t EMPTY = 0ULL;
    public:
        Moves();
        ~Moves();

        void getPawnMoves(int, Bitboard *&, Square *&);
};

#endif //MOVES_H
