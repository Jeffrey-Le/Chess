//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Square {
    private:
        float piece = 0;
        sf::RectangleShape *squareSpace;
    public:
        Square();
        Square(float);
        ~Square();

        void echoPiece();
        void changePiece(float);
        void checkPiece();

        void setColor(sf::Color);
        void setPos(float, float);

        sf::Vector2f usePos();
        sf::RectangleShape useSquare();
        float usePiece();

        bool isClicked(sf::RenderWindow &);
};

#endif //CHESS_SQUARE_H
