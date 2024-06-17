//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Piece.h"

class Square {
    private:
        float piece = 0.0f;
        sf::RectangleShape *squareSpace;
        Piece *occupiedPiece;

        sf::Color color;

        bool isValidMove = false;
        bool isEmpty = true;
    public:
        Square();
        explicit Square(float);
        ~Square();

        void echoPiece() const;
        void changePiece(float);

        void resetState();

        void changeColor(sf::Color) const;

        void setOccupiedPiece(Piece *);
        void setColor(sf::Color);
        void setPos(float, float) const;
        void setValidMove(bool);

        sf::Vector2f usePos() const;
        sf::RectangleShape useSquare() const;
        float usePiece() const;
        Piece *useOccupiedPiece() const;

        bool checkValid() const;
        bool checkEmpty() const;
};

#endif //CHESS_SQUARE_H
