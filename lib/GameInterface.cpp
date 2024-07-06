//
// Created by Crolw on 6/14/2024.
//

#include "../include/GameInterface.h"

GameInterface::GameInterface() {
    std::cout << "Initializing GameInterface \n";

    this->font.loadFromFile("../res/arial.ttf");

    this->turnUI = new sf::Text();
    this->colorUI = new sf::Text();
    this->scoreUI = new sf::Text();

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

    // Initialize ScoreUI
    this->scoreUI->setFont(this->font);
    this->scoreUI->setCharacterSize(30);
    this->scoreUI->setPosition(500.0f, 150.0f);
    this->scoreUI->setString("W: " + std::to_string(points['w']) + " " + "B: " + std::to_string(points['b']));
}

GameInterface::~GameInterface() {
    delete this->turnUI;
    delete this->colorUI;
    delete this->scoreUI;
}

void GameInterface::setTurnCounter(int newCounter) {
    this->turnCounter = newCounter;
    this->setTurnUI();
}

void GameInterface::inverseWhite() {
    this->isWhite = !this->isWhite;
    this->setColorUI();
}

void GameInterface::incrementScore(int const val) {
    if (isWhite)
        points['w'] += abs(val);
    else
        points['b'] += abs(val);

    this->setScoreUI();
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

void GameInterface::setScoreUI() {
    this->scoreUI->setString("W: " + std::to_string(points['w']) + " " + "B: " + std::to_string(points['b']));
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

sf::Text &GameInterface::useScoreUI() const {
    return *this->scoreUI;
}



