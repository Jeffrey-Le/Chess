//
// Created by Jeffrey Vo Le on 5/11/24.
//

#include "../include/pawn.h"

Pawn::Pawn() {
    this->value = 1;

    this->texture.loadFromFile("../res/blackKing.svg");

    this->pieceBoard = new uint64_t(0x00ff000000000000);
}

Pawn::Pawn(char color) {
    this->value = 1;

    if (color == 'w')
    {
        this->pieceBoard = new uint64_t(0x00ff000000000000);
        return;
        }
    if (color == 'b') {
        this->pieceBoard = new uint64_t(0x000000000000ff00);
        return;
    }

    this->pieceBoard = new uint64_t(0);
}