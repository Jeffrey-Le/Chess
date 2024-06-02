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
    public:
        Player();
        ~Player();

        std::string getColor() const;
};

#endif //CHESS_PLAYER_H
