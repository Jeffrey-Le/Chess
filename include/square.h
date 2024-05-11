//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <iostream>

class Square {
    private:
        int piece = 0;
    public:
        Square();
        void echoPiece();
        void changePiece(int);
};

#endif //CHESS_SQUARE_H
