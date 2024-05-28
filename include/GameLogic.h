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
    public:
        GameLogic();
        GameLogic(Board &);
        ~GameLogic();

        void getPossibleMoves(int);

        void displayBitboard(char, char);
        void revertBitboard();

        uint64_t bitwiseAnd(uint64_t, uint64_t);
        uint64_t bitwiseOr(uint64_t, uint64_t);
};

#endif //CHESS_GAMELOGIC_H
