//
// Created by Crolw on 6/7/2024.
//

#ifndef ROOK_H
#define ROOK_H

#include "Pawn.h"

class Rook : public Pawn {
    private:
        bool isCastle = false;
    public:
        Rook();
        explicit Rook(char);
        ~Rook() override;
};


#endif //ROOK_H
