//
// Created by Jeffrey Vo Le on 5/16/24.
//

#ifndef CHESS_GAMELOGIC_H
#define CHESS_GAMELOGIC_H

#include <cstdint>

#include "Bitboard.h"
#include "Board.h"

#include "Pawn.h"
#include "Knight.h"
#include "Moves.h"

// struct Moves {
//     uint64_t FILE_A = 9259542123273814144UL; // 0x0101010101010101
//     //uint64_t FILE_H = 9187201950435737472ULL // 9259542123273814144ULL // 36170086419038336ULL;
//     uint64_t FILE_H = 72340172838076673ULL; // 0x8080808080808080
//     uint64_t FILE_AB = 13889313184910721216ULL; // 0xc0c0c0c0c0c0c0c0
//     uint64_t FILE_GH = 217020518514230019ULL; // 0x0303030303030303
//     uint64_t RANK_1 = 255ULL; // 0x00000000000000ff
//     uint64_t RANK_4 = 4278190080ULL; // 0x00000000ff000000
//     uint64_t RANK_5 = 1095216660480; // 0x000000ff00000000
//     uint64_t RANK_8 = 18374686479671623680ULL; // 0xff00000000000000
//     uint64_t CENTRE = 103481868288ULL; // 0x0000001818000000
//     uint64_t EXTENDED_CENTRE = 1125899906580480ULL; // 0x00003fffffffc0000
//     uint64_t KING_SIDE = 1085102592571150095ULL; // 0x0f0f0f0f0f0f0f0f
//     uint64_t QUEEN_SIDE = 17361641481138401520ULL; // 0xf0f0f0f0f0f0f0f0
//     uint64_t KING_B7 = 18014398509481984ULL; // 0x0040000000000000
//     uint64_t KNIGHT_C6 = 35184372088832ULL; // 0x0000200000000000
//     uint64_t NOT_WHITE_PIECES = 0ULL;
//     uint64_t BLACK_PIECES = 0ULL;
//     uint64_t EMPTY = 0ULL;
// };

class GameLogic {
    private:
        // General Logic
        bool playerTurn = false;

        bool enPeasant = true;

        int turnCounter = 0;
        // Keep Board State
        Board *curBoard;
        Bitboard *curBitboard;

        // Initialize Bitboards for each Piece
        Bitboard *whitePawn;
        Bitboard *whiteRook;
        Bitboard *whiteKnight;
        Bitboard *whiteBishop;
        Bitboard *whiteQueen;
        Bitboard *whiteKing;

        Bitboard *blackPawn;
        Bitboard *blackRook;
        Bitboard *blackKnight;
        Bitboard *blackBishop;
        Bitboard *blackQueen;
        Bitboard *blackKing;

        void setIntialBoard();
    public:
        GameLogic();
        GameLogic(Board &);
        ~GameLogic();

        void getPossibleMoves(int);

        void displayBitboard(char, char);
        void revertBitboard();

        uint64_t bitwiseAnd(uint64_t, uint64_t);
        uint64_t bitwiseOr(uint64_t, uint64_t);

        Moves move;
};

#endif //CHESS_GAMELOGIC_H
