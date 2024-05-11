//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Square {
    private:
        int piece = 0;
        sf::RectangleShape *squareSpace;
    public:
        Square();

        void echoPiece();
        void changePiece(int);

        void setColor(sf::Color);
        void setPos(float, float);

        sf::Vector2f usePos();
        sf::RectangleShape useSquare();
};

#endif //CHESS_SQUARE_H
