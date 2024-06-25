//
// Created by Crolw on 6/7/2024.
//

#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Pawn.h"

class King : public Pawn {
    private:
        bool inCheck = false;
    public:
        King();
        explicit King(char);
        ~King() override;

        bool isCheck() const;
        void setCheck(bool);
};

#endif //KING_H
