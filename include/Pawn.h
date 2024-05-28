//
// Created by Jeffrey Vo Le on 5/11/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    private:
        bool firstMove = false;
    public:
        Pawn();
        Pawn(char);

};

#endif //CHESS_PAWN_H
