//
// Created by Jeffrey Vo Le on 7/21/24.
//

#include "../include/Promotion.h"

Promotion::Promotion() {
    this->container = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));

    this->pieces.push_back(new Knight);
    this->pieces.push_back(new Bishop);
    this->pieces.push_back(new Rook);
    this->pieces.push_back(new Queen);
}

Promotion::Promotion(char const color) {
    this->container = new sf::RectangleShape(sf::Vector2f(200.0f, 50.0f));

    this->pieces.push_back(new Knight(color));
    this->pieces.push_back(new Bishop(color));
    this->pieces.push_back(new Rook(color));
    this->pieces.push_back(new Queen(color));
}

Promotion::~Promotion() {
    delete this->container;

    for (auto &piece: this->pieces)
        delete piece;
}

void Promotion::drawPromotionUI(sf::Vector2f squarePos) {
    this->container->setPosition(squarePos.x, squarePos.y - 30.0f);

    for (int i = 0; i < 4; i++)
    {
        auto const newX = this->container->getPosition().x + (float(i)*50.0f);

        this->pieces[i]->setPosition(newX, this->container->getPosition().y);
    }
}

sf::RectangleShape Promotion::usePromUI() {
    return *this->container;
}

std::vector<Piece *> Promotion::usePromPieces() {
    return this->pieces;
}
