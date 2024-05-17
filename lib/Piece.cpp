//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Piece.h"


Piece::Piece() {
    this->pieceBoard = new uint64_t(0);
}

Piece::Piece(uint64_t *bitBoard) {
    this->pieceBoard = bitBoard;
}

Piece::~Piece() {
    delete this->pieceBoard;
};


void Piece::setValue(int newValue) {
    this->value = newValue;
}

void Piece::setTexture(sf::Texture newTextureObj) {
    this->texture = newTextureObj;
}

void Piece::setTexture(std::string pathToTexture) {
    if (!this->texture.loadFromFile(pathToTexture))
        std::cout << "Error Loading New Texture from file path:" << std::endl << pathToTexture << std::endl;
}


void Piece::setBitBoard(uint64_t *newBitBoard) {
    this->pieceBoard = newBitBoard;
}

sf::Sprite Piece::useSprite() {
    return this->sprite;
}

void Piece::displayBoard() {
    std::cout << *this->pieceBoard << "\n";
}
