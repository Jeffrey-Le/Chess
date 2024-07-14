//
// Created by Crolw on 5/31/2024.
//


#ifndef MOVES_H
#define MOVES_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Bitboard.h"
#include "Pawn.h"

class Moves {
    private:
        uint64_t FILE_A = 72340172838076673ULL; // 0x8080808080808080
        uint64_t FILE_H = 9259542123273814144UL; // 0x0101010101010101
        uint64_t FILE_AB = 217020518514230019ULL; // 0x0303030303030303
        uint64_t FILE_GH = 13889313184910721216ULL; // 0xc0c0c0c0c0c0c0c0
        uint64_t RANK_1 = 18374686479671623680ULL; // 0xff00000000000000
        uint64_t RANK_4 = 1095216660480; // 0x000000ff00000000
        uint64_t RANK_5 = 4278190080ULL; // 0x00000000ff000000
        uint64_t RANK_8 = 255ULL; // 0x00000000000000ff
        uint64_t CENTRE = 103481868288ULL; // 0x0000001818000000
        uint64_t EXTENDED_CENTRE = 66229406269440ULL; // 0x00003c3c3c3c0000
        uint64_t KING_SIDE = 17361641481138401520ULL; // 0xf0f0f0f0f0f0f0f0
        uint64_t QUEEN_SIDE = 1085102592571150095ULL; // 0x0f0f0f0f0f0f0f0f
        uint64_t KING_B7 = 512ull;//18014398509481984ULL; // 0x0040000000000000
        uint64_t KNIGHT_C6 = 262144ull;//35184372088832ULL; // 0x0000200000000000
        uint64_t PLAYER_PIECES = 0ULL;
        uint64_t OPPOSING_PIECES = 0ULL;
        uint64_t EMPTY = 0ULL;
    public:
        Moves();
        ~Moves();

        std::vector<uint64_t> getPawnMoves(int, Bitboard *&, Square *&, int enPeasantPos = -1) const;
        std::vector<uint64_t> getKnightMoves(int, Bitboard *&, Square *&) const;
        std::vector<uint64_t> getBishopMoves(int, Bitboard *&, Square *&) const;
        std::vector<uint64_t> getRookMoves(int, Bitboard *&, Square *&) const;
        std::vector<uint64_t> getQueenMoves(int, Bitboard *&, Square *&) const;
        std::vector<uint64_t> getKingMoves(int, std::unordered_map<float, Bitboard*>, Bitboard *&, Square *&);
        std::vector<uint64_t> generateKingMoves(int, Bitboard*&) const;

        // Helper Functions
        void blackOrWhite(bool , uint64_t, uint64_t &, int) const;
        static bool checkKingInCheck(std::vector<uint64_t> const&, uint64_t);


        // Setter Functions
        void setPlayerP(uint64_t);
        void setOpposingP(uint64_t);
        void setEmpty(uint64_t);

        // Use Functions
        uint64_t useOpposingP() const;
};

#endif //MOVES_H
