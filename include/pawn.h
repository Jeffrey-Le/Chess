//
// Created by Jeffrey Vo Le on 5/11/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "piece.h"

class Pawn : public Piece {
    private:
        uint64_t *pieceBoard;
    public:
        Pawn();

        virtual void displayBoard();
};

#endif //CHESS_PAWN_H
