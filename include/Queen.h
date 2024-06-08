//
// Created by Crolw on 6/7/2024.
//

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
    public:
        Queen();
        explicit Queen(char);
        ~Queen() override;
};

#endif //QUEEN_H
