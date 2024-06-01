//
// Created by Crolw on 5/31/2024.
//

#include "../include/Moves.h"

Moves::Moves() {

}

Moves::~Moves() {

}

void Moves::getPawnMoves(int val, Bitboard *&board, Square *&squares) {
    std::cout << "In Pawn Moves" << std::endl;

    // Check Capture Right
    uint64_t pawnMoves = (board->useBitboard()>>7) & this->BLACK_PIECES & ~this->RANK_8 & ~this->FILE_H;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves>>i) & 1) == 1) {
            squares[i].setColor(sf::Color(255, 0, 0));
            std::cout << "Setting Color" << std::endl;
        }
    }

    // Check Capture Left
    pawnMoves = (board->useBitboard()>>9) & this->BLACK_PIECES & ~this->RANK_8 & this->FILE_A;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves>>i) & 1) == 1) {
            squares[i].setColor(sf::Color(0, 255, 0));
            std::cout << "Setting Color" << std::endl;
        }
    }

    // Move 1 Square
    // board >> 8  && EMPTY && ~RANK8

    // Move 2 Square
    // board >> 16  && EMPTY && ~RANK8

    // -- Promotions --

    // Promotion while Capture Right
    // board >> 7 & BLACK & RANK8 & ~FILEH

    // Promotion while Capture Left
    // board >> 9 & BLACK & RANK8 & ~FILEH

    // Promotion Move 1 Square
    // board >> 8  & EMPTY & RANK8 & ~FILEH

}
