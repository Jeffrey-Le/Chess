//
// Created by Crolw on 6/7/2024.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    public:
        Rook();
        explicit Rook(char);
        ~Rook() override;
};


#endif //ROOK_H
