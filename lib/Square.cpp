//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include <cmath>

#include "../include/Square.h"

Square::Square() {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);

    this->occupiedPiece = new Piece();
}

Square::Square(float const pieceVal) {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);
    this->piece = pieceVal;

    this->occupiedPiece = new Piece();
}

Square::~Square() {
    delete this->squareSpace;
    delete this->occupiedPiece;
}

void Square::echoPiece() const{
    std::cout << this->piece << std::endl << int(std::floor(this->piece)) << std::endl;
}

void Square::changePiece(float const changedPiece) {
    this->piece = changedPiece;
    this->isEmpty = false;
}

bool Square::checkClickable() {
    if (this->isValidMove) {
        this->isValidMove = false;

        return true;
    }

    return false;
}



void Square::changeColor(sf::Color const color) const {
    this->squareSpace->setFillColor(color);
}

void Square::setColor(sf::Color const color) {
    this->squareSpace->setFillColor(color);
    this->color = color;
}

void Square::setPos(float const x, float const y) const {
    this->squareSpace->setPosition(x, y);
}

void Square::setValidMove(bool const val) {
    this->isValidMove = val;
}

sf::Vector2f Square::usePos() const {
    return this->squareSpace->getPosition();
}

sf::RectangleShape Square::useSquare() const {
    return *this->squareSpace;
}

float Square::usePiece() const {
    return this->piece;
}

bool Square::isClicked(sf::RenderWindow const &window) {
    if (!this->isEmpty)
        return true;

    return false;
}

void Square::setOccupiedPiece(Piece *newPiece) {
    this->occupiedPiece = newPiece;
    this->changePiece(this->occupiedPiece->useVal());

    // Sets Position
    sf::Vector2f const pos = this->squareSpace->getPosition();

    this->occupiedPiece->setPosition(pos.x, pos.y);

}

Piece *Square::useOccupiedPiece() const {
    if (this->occupiedPiece == nullptr)
        return nullptr;

    return this->occupiedPiece;
}

void Square::resetState() {

    std::cout << "Resetting State" << std::endl;

    this->setColor(this->color);

    if (this->occupiedPiece == nullptr || this->piece == 0.0f) {
        this->isEmpty = true;
    }
}


