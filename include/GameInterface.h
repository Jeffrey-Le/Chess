//
// Created by Crolw on 6/14/2024.
//

#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class GameInterface {
    private:
        int turnCounter = 0;
        bool isWhite = true;
        std::unordered_map<char, int> points = {{'w', 0}, {'b', 0}};

        sf::Font font;

        sf::Text *turnUI;
        sf::Text *colorUI;
        sf::Text *scoreUI;
    public:
        GameInterface();
        ~GameInterface();

        void setTurnCounter(int);
        void inverseWhite();
        void incrementScore(int);

        void setTurnUI();
        void setColorUI();
        void setScoreUI();

        // Use Functions
        int useTurnCounter() const;

        sf::Text &useTurnUI() const;
        sf::Text &useColorUI() const;
        sf::Text &useScoreUI() const;
};

#endif //GAMEINTERFACE_H
