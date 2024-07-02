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
        float value; // How to track piece in Classes

        bool isWhite = true;

        sf::Texture texture;
        sf::Sprite sprite;

    public:
        Piece();
        explicit Piece(bool);
        virtual ~Piece() = default;

        void setPosition(float, float);

        void setValue(float);

        void setTexture(sf::Texture const &);

        void setTexture(std::string const &);

        sf::Sprite useSprite();

        float useVal() const;

        bool checkWhite() const;
};

#endif //CHESS_PIECE_H
