//
// Created by Jeffrey Vo Le on 5/11/24.
//

#include "../include/pawn.h"

Pawn::Pawn() {
    this->value = 1;

    this->pieceBoard = new uint64_t(0x0000000000000004);
}

void Pawn::displayBoard() {
    std::cout << *this->pieceBoard << "\n";
}