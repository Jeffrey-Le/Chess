//
// Created by Crolw on 6/7/2024.
//

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    public:
        King();
        explicit King(char);
        ~King() override;
};

#endif //KING_H
