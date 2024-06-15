//
// Created by Crolw on 6/14/2024.
//

#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class GameInterface {
    private:
        int turnCounter = 0;
        bool isWhite = true;


        sf::Font font;

        sf::Text *turnUI;
        sf::Text *colorUI;
    public:
        GameInterface();
        ~GameInterface();

        void setTurnCounter(int);
        void inverseWhite();

        void setTurnUI();
        void setColorUI();

        // Use Functions
        int useTurnCounter() const;

        sf::Text &useTurnUI() const;
        sf::Text &useColorUI() const;
};

#endif //GAMEINTERFACE_H
