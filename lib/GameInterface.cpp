//
// Created by Crolw on 6/14/2024.
//

#include "../include/GameInterface.h"

GameInterface::GameInterface() {
    std::cout << "Initializing GameInterface \n";

    this->font.loadFromFile("../res/arial.ttf");

    this->turnUI = new sf::Text();
    this->colorUI = new sf::Text();

    // Initialize TurnUI
    this->turnUI->setFont(this->font);
    this->turnUI->setString(std::to_string(this->turnCounter));
    this->turnUI->setCharacterSize(30);
    this->turnUI->setPosition(530.0f, 50.0f);

    // Initialize ColorUI
    this->colorUI->setFont(this->font);
    this->colorUI->setCharacterSize(30);
    this->colorUI->setPosition(500.0f, 100.0f);
    this->colorUI->setString("White");

}

GameInterface::~GameInterface() {
    delete this->turnUI;
    delete this->colorUI;
}

void GameInterface::setTurnCounter(int newCounter) {
    this->turnCounter = newCounter;
    this->setTurnUI();

}

void GameInterface::inverseWhite() {
    this->isWhite = !this->isWhite;
    this->setColorUI();
}

void GameInterface::setTurnUI() {
    this->turnUI->setString(std::to_string(this->turnCounter));
}

void GameInterface::setColorUI() {
    if (isWhite)
        this->colorUI->setString("White");
    else
        this->colorUI->setString("Black");
}

// Use Functions
int GameInterface::useTurnCounter() const {
    return this->turnCounter;
}

sf::Text &GameInterface::useTurnUI() const {
    return *this->turnUI;
}

sf::Text &GameInterface::useColorUI() const {
    return *this->colorUI;
}



