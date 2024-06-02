//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Square.h"

Square::Square() {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);

    this->occupiedPiece = new Piece();
}

Square::Square(float pieceVal) {
    std::cout << "Initializing Square \n";

    this->squareSpace = new sf::RectangleShape(sf::Vector2f(50.f, 50.f));
    this->squareSpace->setPosition(0.f, 0.f);
    this->piece = pieceVal;

    this->occupiedPiece = new Piece();
}

Square::~Square() {
    delete this->squareSpace;
}

void Square::echoPiece() const{
    std::cout << this->piece << std::endl << int(floor(this->piece)) << std::endl;
}

void Square::changePiece(float changedPiece) {
    this->piece = changedPiece;
    this->isEmpty = false;
}

void Square::checkPiece() const{
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


bool Square::checkClickable(sf::RenderWindow const &window, Piece *newPiece, float const pieceValue) {
    sf::Vector2i const mouseCoords = sf::Mouse::getPosition(window);

    if (this->squareSpace->getGlobalBounds().contains(mouseCoords.x, mouseCoords.y) && this->isValidMove) {
        std::cout << "In Check Clickable" << std::endl;
        this->setOccupiedPiece(newPiece);
        this->changePiece(pieceValue);

        this->isValidMove = false;

        return true;
    }

    this->isValidMove = false;

    return false;
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

    sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);

    // Means a Piece is on the board
    if (this->squareSpace->getGlobalBounds().contains(mouseCoords.x, mouseCoords.y) && !this->isValidMove && !this->isEmpty) {
        std::cout << "Square in IsClicked" << std::endl;
        this->squareSpace->setFillColor(sf::Color(0, 0, 175, 150));
        return true;
    }

    if (this->squareSpace->getFillColor() != this->color)
        this->squareSpace->setFillColor(this->color);

    // if (this->piece == 0.0f && this->isEmpty)
    //     this->isValidMove = true;

    return false;
}

void Square::setOccupiedPiece(Piece *newPiece) {

    if (newPiece->useVal() == 0.0f) {
        this->occupiedPiece = newPiece;
        this->changePiece(0.0f);
        this->isEmpty = true;
    }
    else {
        this->occupiedPiece = newPiece;
        //this->occupiedPiece->displayBoard();
        this->changePiece(this->occupiedPiece->useVal());

        // Sets Position
        sf::Vector2f const pos = this->squareSpace->getPosition();

        this->occupiedPiece->setPosition(pos.x, pos.y);
    }

}

Piece *Square::useOccupiedPiece() const {
    if (this->occupiedPiece == nullptr)
        return nullptr;

    return this->occupiedPiece;
}

void Square::resetState() {

    std::cout << "REsetting State" << std::endl;

    this->setColor(this->color);

    if (this->occupiedPiece == nullptr || this->piece == 0.0f) {
        this->isEmpty = true;
    }
}


