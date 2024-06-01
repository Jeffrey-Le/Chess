//
// Created by Crolw on 5/31/2024.
//

#include "../include/Moves.h"

Moves::Moves() {

}

Moves::~Moves() {

}

void Moves::getPawnMoves(int val, Bitboard *&board, Square *&squares) const {
    std::cout << "In Pawn Moves" << std::endl;

    uint64_t const BITBOARD = board->useBitboard();

    // Check Capture Right
    uint64_t pawnMoves = (BITBOARD >> 7) & this->BLACK_PIECES & ~this->RANK_8 & ~this->FILE_H;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(255, 0, 0));
            std::cout << "Pawn Capture Right" << std::endl;
        }
    }

    // Check Capture Left
    pawnMoves = (BITBOARD >> 9) & this->BLACK_PIECES & ~this->RANK_8 & this->FILE_A;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(0, 255, 0));
            std::cout << "Pawn Capture Left" << std::endl;
        }
    }

    // Move 1 Square
    // board >> 8  && EMPTY && ~RANK8
    pawnMoves = (BITBOARD >> 8) & this->EMPTY & ~this->RANK_8;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(0, 255, 0));
            std::cout << "Pawn Move Forward 1" << std::endl;
        }
    }

    // Move 2 Square
    // board >> 16  && EMPTY && ~RANK8
    pawnMoves = (BITBOARD >> 16) & this->EMPTY & ~this->RANK_8 & ~this->FILE_H;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(0, 255, 0));
            std::cout << "Pawn Move Forward 2" << std::endl;
        }
    }

    // -- Promotions --

    // Promotion while Capture Right
    // board >> 7 & BLACK & RANK8 & ~FILEH
    pawnMoves = (BITBOARD >> 7) & this->BLACK_PIECES & this->RANK_8 & ~this->FILE_H;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(255, 0, 0));
            std::cout << "Pawn Capture Right Promotion" << std::endl;
        }
    }

    // Promotion while Capture Left
    // board >> 9 & BLACK & RANK8 & ~FILEH
    pawnMoves = (BITBOARD >> 9) & this->BLACK_PIECES & this->RANK_8 & ~this->FILE_H;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(255, 0, 0));
            std::cout << "Pawn Capture Left Promotion" << std::endl;
        }
    }

    // Promotion Move 1 Square
    // board >> 8  & EMPTY & RANK8 & ~FILEH
    pawnMoves = (BITBOARD >> 8) & this->EMPTY & this->RANK_8 & ~this->FILE_H;
    for (int i = 0; i < 64; i++) {
        if (((pawnMoves >> i) & 1) == 1) {
            squares[i].setColor(sf::Color(255, 0, 0));
            std::cout << "Pawn Move Forward 1 Promotion" << std::endl;
        }
    }

}
