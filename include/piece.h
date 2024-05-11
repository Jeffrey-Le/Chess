//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <iostream>
#include <cstdint>
#include <SFML/Graphics.hpp>

class Piece {
    protected:
        uint64_t *pieceBoard;
        int value;
        sf::Image texture;
    public:
        Piece();

        void setValue(int);

        void setTexture(sf::Image);

        void displayBoard();
};

#endif //CHESS_PIECE_H
