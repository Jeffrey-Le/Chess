//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/square.h"

Square::Square() {
    std::cout << "Initializing Square \n";
}

void Square::echoPiece() {
    std::cout << this->piece;
}

void Square::changePiece(int changedPiece) {
    this->piece = changedPiece;
}