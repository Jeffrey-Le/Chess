//
// Created by Jeffrey Vo Le on 5/11/24.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    private:
        bool firstMove = true;
    public:
        Pawn();
        explicit Pawn(char);
        ~Pawn() override;

        bool checkFirstMove();

    void setFirstMove();

};

#endif //CHESS_PAWN_H
