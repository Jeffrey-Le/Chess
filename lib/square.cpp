//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/square.h"

Square::Square() {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);
}

void Square::echoPiece() {
    std::cout << this->piece;
}

void Square::changePiece(int changedPiece) {
    this->piece = changedPiece;
}

void Square::setColor(sf::Color color) {
    this->squareSpace->setFillColor(color);
}

void Square::setPos(float x, float y) {
    this->squareSpace->setPosition(x, y);
}


sf::Vector2f Square::usePos() {
    return this->squareSpace->getPosition();
}

sf::RectangleShape Square::useSquare() {
    return *this->squareSpace;
}


