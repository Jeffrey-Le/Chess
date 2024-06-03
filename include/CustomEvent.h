//
// Created by Jeffrey Vo Le on 5/18/24.
//

#ifndef CHESS_CUSTOMEVENT_H
#define CHESS_CUSTOMEVENT_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "GameLogic.h"
#include "Square.h"
#include "Piece.h"

class CustomEvent {
    private:
        sf::Event event;
        GameLogic *logic;
    public:
        CustomEvent();
        explicit CustomEvent(GameLogic *&);

        void squareClickLogic(sf::RenderWindow const &, Square *, Square *&, int index) const;
        static void occupiedSquareClick(Square *&, Square *&);
        static void emptySquareClick(Square *&, Square *&) ;

        void resetAllSquareStates();

        sf::Event useCustomEvent() const;
};

#endif //CHESS_CUSTOMEVENT_H
