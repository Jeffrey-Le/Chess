//
// Created by Jeffrey Vo Le on 5/16/24.
//

#ifndef CHESS_GAMELOGIC_H
#define CHESS_GAMELOGIC_H

#include <cstdint>
#include <unordered_map>
#include <functional>
#include <memory>

#include "Bitboard.h"
#include "Board.h"

#include "Pawn.h"
#include "Knight.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

#include "Moves.h"
#include "Player.h"

class GameLogic {
    private:
        Moves moves;

        Player *players; // 1 or 2

        // General Logic
        bool playerTurn = true; // true = player 1, false = player 2 or AI

        bool enPeasant = true; // true = start of game, false = condition fails

        bool kingInCheck = false;

        int turnCounter = 0;

        // Keep Board State
        Board *curBoard; // GUI
        Bitboard *curBitboard; // Game State

        // Initialize Bitboards for each Piece
        std::unordered_map<float, Bitboard*> bitBoards;

        Bitboard *possibleMoves;
        Bitboard *validSquares;

        std::vector<int> attackingIndices; // Stores Indices of Attacking Pieces (Max is 2)
        std::unordered_map<uint64_t, bool> attackChecks; // Stores each capturing move direction: <Move, CausesCheck>

        void setIntialBoard();
    public:
        GameLogic();
        explicit GameLogic(Board &);
        ~GameLogic();

        void getPossibleMoves(int);
        void getPossibleMovesInCheck();

        // Helpers
        std::vector<uint64_t> generateMoves(int);
        std::unordered_map<char, int> findKingPositions();
        King* getPlayerKing();
        void testKingInCheck();

        // Updates
        void updateValidSquare();
        void updateMoves(int, int);
        void updateBoard(Board *&);
        void standbyUpdate();

        void displayBitboard(char, char);

        // Resets
        void revertBitboard();
        void resetPossibleMoves();

        // Bitwise Functions
        static uint64_t bitwiseAnd(Bitboard *&, Bitboard *&);
        static uint64_t bitwiseOr(Bitboard *&, Bitboard *&);
        static uint64_t bitwiseNot(Bitboard *&);

        static uint64_t bitwiseAnd(uint64_t, uint64_t);
        static uint64_t bitwiseOr(uint64_t, uint64_t);
        static uint64_t bitwiseNot(uint64_t);
};

#endif //CHESS_GAMELOGIC_H
