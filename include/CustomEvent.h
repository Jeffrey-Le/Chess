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
        CustomEvent(GameLogic *&);

        void squareClickLogic(sf::RenderWindow const&, Square *&, Square *&, sf::Event &);

        sf::Event useCustomEvent();
};

#endif //CHESS_CUSTOMEVENT_H
