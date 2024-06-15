//
// Created by Jeffrey Vo Le on 5/14/24.
//

#include "../include/Player.h"

Player::Player() {
    this->color = new sf::Color(255, 255, 255, 255);
    this->colorString = "White";
}

Player::~Player() {
    delete this->color;
}

std::string Player::getColor() const{
    return this->colorString;
}

void Player::setColor(std::string colorString) {
    std::transform(colorString.begin(), colorString.end(), colorString.begin(), [](unsigned char c) {return std::tolower(c);});

    if (colorString == "black")
        this->colorString = "Black";

    if (colorString == "white")
        this->colorString = "White";
}
