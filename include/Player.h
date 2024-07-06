//
// Created by Jeffrey Vo Le on 5/14/24.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Player {
    private:
        std::string colorString; // Player Color is Unknown until Game Starts
        sf::Color *color; // Color will be used to track which piece belongs to the Player

        int turn = 1;
    public:
        Player();
        ~Player();

        std::string getColor() const;
        void setColor(std::string);

        void incrementTurn();

        int useTurn();
};

#endif //CHESS_PLAYER_H
