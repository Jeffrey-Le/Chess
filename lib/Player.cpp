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
