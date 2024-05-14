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
        sf::Texture texture;
        sf::Sprite sprite;
    public:
        Piece();
        Piece(uint64_t*);
        ~Piece();

        void setValue(int);

        void setTexture(sf::Texture);

        void setTexture(std::string);

        void setBitBoard(uint64_t*);

        sf::Sprite useSprite();

        void displayBoard();
};

#endif //CHESS_PIECE_H
