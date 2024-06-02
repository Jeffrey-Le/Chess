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
#include "Player.h"

class GameLogic {
    private:
        //Players
        Player *players; // 1 or 2

        // General Logic
        bool playerTurn = false; // true = player 1, false = player 2 or AI

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

        void setIntialBoard() const;
    public:
        GameLogic();
        explicit GameLogic(Board &);
        ~GameLogic();

        void getPossibleMoves(int);
        void updateMoves(int);

        void displayBitboard(char, char) const;
        void revertBitboard() const;

        static uint64_t bitwiseAnd(Bitboard *&, Bitboard *&);
        static uint64_t bitwiseOr(Bitboard *&, Bitboard *&);

        static uint64_t bitwiseAnd(uint64_t, uint64_t);
        static uint64_t bitwiseOr(uint64_t, uint64_t);

        Moves move;
};

#endif //CHESS_GAMELOGIC_H
