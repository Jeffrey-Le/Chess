//
// Created by Crolw on 6/7/2024.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
    public:
        Bishop();
        explicit Bishop(char);
        ~Bishop() override;
};

#endif //BISHOP_H
