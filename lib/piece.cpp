//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/piece.h"


Piece::Piece() {

}

Piece::Piece(uint64_t *bitBoard) {
    this->pieceBoard = bitBoard;
}


void Piece::setValue(int newValue) {
    this->value = newValue;
}

void Piece::setTexture(sf::Image newTexture) {
    this->texture = newTexture;
}

void Piece::setBitBoard(uint64_t *newBitBoard) {
    this->pieceBoard = newBitBoard;
}

void Piece::displayBoard() {
    std::cout << *this->pieceBoard << "\n";
}
