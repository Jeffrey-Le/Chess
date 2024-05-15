//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/square.h"

Square::Square() {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);
}

Square::Square(float pieceVal) {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);
    this->piece = pieceVal;
}

Square::~Square() {
    delete this->squareSpace;
}

void Square::echoPiece() {
    std::cout << this->piece << std::endl << int(floor(this->piece)) << std::endl;
}

void Square::changePiece(float changedPiece) {
    this->piece = changedPiece;
}

void Square::checkPiece() {
    switch (int(floor(this->piece)))
    {
        case 1:
            // Pawn
            std::cout << "Pawn" << std::endl;
            break;
        case 3:
            if (this->piece == 3.1f)
            {
                // Knight
                std::cout << "Knight" << std::endl;
            }
            else
            {
                // Bishop
                std::cout << "Bishop" << std::endl;
            }
            break;
        case 5:
            // Rook
            std::cout << "Rook" << std::endl;
            break;
        case 9:
            // Queen
            std::cout << "Queen" << std::endl;
            break;
        default:
            // King
            std::cout << "King" << std::endl;
    }

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

float Square::usePiece() {
    return this->piece;
}

bool Square::isClicked(sf::RenderWindow &window) {

    sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);

    if (this->squareSpace->getGlobalBounds().contains(mouseCoords.x, mouseCoords.y)) {
        return true;
    }
}

