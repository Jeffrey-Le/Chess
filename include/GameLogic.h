//
// Created by Jeffrey Vo Le on 5/16/24.
//

#ifndef CHESS_GAMELOGIC_H
#define CHESS_GAMELOGIC_H

#include <cstdint>

#include "Bitboard.h"
#include "Board.h"

class GameLogic {
    private:
        // Keep Board State
        Board *curBoard;
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

        void displayBitboard(char, char);
        void revertBitboard();
};

#endif //CHESS_GAMELOGIC_H
