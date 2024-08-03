//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Square.h"
#include "Board.h"
#include "Bitboard.h"
#include "GameLogic.h"
#include "GameInterface.h"

class Game {
    private:
        sf::RenderWindow window;
        Board *board;
        GameInterface *interface;
    public:
        Game();
        ~Game();
        void openGame();

        void endState(GameLogic *&, bool &);
};

#endif //CHESS_GAME_H
