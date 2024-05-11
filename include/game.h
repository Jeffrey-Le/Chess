//
// Created by Jeffrey Vo Le on 5/10/24.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Game {
    private:
        sf::RenderWindow window;
    public:
        Game();
        void openGame();
};

#endif //CHESS_GAME_H
