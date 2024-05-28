//
// Created by Jeffrey Vo Le on 5/18/24.
//

#ifndef CHESS_CUSTOMEVENT_H
#define CHESS_CUSTOMEVENT_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Square.h"
#include "Piece.h"

class CustomEvent {
    private:
        sf::Event event;
    public:
        CustomEvent();

        Piece *squareClickLogic(sf::RenderWindow &, Square *, Piece *);

        sf::Event useCustomEvent();
};

#endif //CHESS_CUSTOMEVENT_H
