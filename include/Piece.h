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
        uint64_t *pieceBoard; // How to track piece on Board

        float value; // How to track piece in Classes

        bool isWhite = true;

        sf::Texture texture;
        sf::Sprite sprite;
    public:
        Piece();
        explicit Piece(uint64_t*, bool);
        virtual ~Piece();

        void setPosition(float, float);

        void setValue(float);

        void setTexture(sf::Texture const &);

        void setTexture(std::string const &);

        void setBitBoard(uint64_t*);

        sf::Sprite useSprite();

        float useVal() const;

        void displayBoard() const;

        bool checkWhite();
};

#endif //CHESS_PIECE_H
