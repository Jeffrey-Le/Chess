//
// Created by Crolw on 5/31/2024.
//

#include "../include/Moves.h"

Moves::Moves() {

}

Moves::~Moves() {

}

uint64_t Moves::getPawnMoves(int const index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Pawn Moves" << std::endl;

    uint64_t const temp = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (temp);

    // Check Capture Right
    uint64_t pawnMoves = (BITBOARD >> 7) & this->BLACK_PIECES & ~this->RANK_8 & ~this->FILE_A;

    // Check Capture Left
    pawnMoves |= (BITBOARD >> 9) & this->BLACK_PIECES & ~this->RANK_8 & ~this->FILE_H;

    // Move 1 Square
    // board >> 8  && EMPTY && ~RANK8
    pawnMoves |= (BITBOARD >> 8) & this->EMPTY & ~this->RANK_8;

    // Guarenteed to be a Pawn Dervied Class
    Pawn* pawn = dynamic_cast<Pawn*>(squares[index].useOccupiedPiece());

    // Move 2 Square
    // board >> 16  && EMPTY && ~RANK8 && ~FILEH
    if (pawn->checkFirstMove()) {
        pawn->setFirstMove();
        std::cout << "Two Spaces" << std::endl;

        pawnMoves |= (BITBOARD >> 16) & this->EMPTY & ~this->RANK_8 & ~this->FILE_H;
    }
    // -- Promotions --

    // Promotion while Capture Right
    // board >> 7 & BLACK & RANK8 & ~FILEH
    pawnMoves |= (BITBOARD >> 7) & this->BLACK_PIECES & this->RANK_8 & ~this->FILE_A;

    // Promotion while Capture Left
    // board >> 9 & BLACK & RANK8 & ~FILEH
    pawnMoves |= (BITBOARD >> 9) & this->BLACK_PIECES & this->RANK_8 & ~this->FILE_H;

    // Promotion Move 1 Square
    // board >> 8  & EMPTY & RANK8 & ~FILEH
    pawnMoves |= (BITBOARD >> 8) & this->EMPTY & this->RANK_8 & ~this->FILE_H;

    return pawnMoves;
}

uint64_t Moves::getKnightMoves(int const index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Knight Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    int curFile = index % 8;

    uint64_t knightMoves = 0ULL;

    if ((newSpaceMask & this->FILE_A) == 0ULL) {
        // Check Moves Right Up
        knightMoves |= ((BITBOARD >> 15) | (BITBOARD >> 6)) & ~this->FILE_AB & ~this->RANK_1;

        // Check Moves Right Down
        knightMoves |= ((BITBOARD << 17) | (BITBOARD << 10)) & ~this->FILE_AB & ~this->RANK_8;
    }
    else {
        // Check Moves Right Up
        knightMoves |= ((BITBOARD >> 15) | (BITBOARD >> 6)) & ~this->FILE_A & ~this->RANK_1;

        // Check Moves Right Down
        knightMoves |= ((BITBOARD << 17) | (BITBOARD << 10)) & ~this->FILE_A & ~this->RANK_8;
    }


    if ((newSpaceMask & this->FILE_H) == 0ULL) {
        // Check Moves Left Up
        knightMoves |= ((BITBOARD >> 17) | (BITBOARD >> 10)) & ~this->FILE_GH & ~this->RANK_1;

        // Check Moves Left Down
        knightMoves |= ((BITBOARD << 15) | (BITBOARD << 6)) & ~this->FILE_GH & ~this->RANK_8;
    }
    else {
        // Check Moves Left Up
        knightMoves |= ((BITBOARD >> 17) | (BITBOARD >> 10)) & ~this->FILE_H & ~this->RANK_1;

        // Check Moves Left Down
        knightMoves |= ((BITBOARD << 15) | (BITBOARD << 6)) & ~this->FILE_H & ~this->RANK_8;
    }


    knightMoves &= ~(this->NOT_WHITE_PIECES);

    return knightMoves;

}

uint64_t Moves::getBishopMoves(int const index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Bishop Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    int curFile = index % 8;

    // Check Right Moves
    uint64_t bishopMoves = 0ULL;

    // Check each other Ranks (7 Ranks) Up Moves
    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_WHITE_PIECES & (BITBOARD >> (7 * i))) != 0ULL)
            break;

        if ((curFile + i) < 8 )
            bishopMoves |= (BITBOARD >> (7 * i)) & ~this->FILE_A;

    }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_WHITE_PIECES & (BITBOARD >> (9 * i))) != 0ULL)
            break;

        if ((curFile - i) >= 0)
            bishopMoves |= (BITBOARD >> (9 * i)) & ~this->FILE_H;
    }

    bishopMoves |= bishopMoves & ~this->RANK_1;

    // Down Moves
    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_WHITE_PIECES & (BITBOARD << (9 * i))) != 0ULL)
            break;

        if ((curFile + i) < 8)
            bishopMoves |= (BITBOARD << (9 * i)) & ~this->FILE_A;
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_WHITE_PIECES & (BITBOARD << (7 * i))) != 0ULL)
            break;

        if ((curFile - i) >= 0)
            bishopMoves |= (BITBOARD << (7 * i)) & ~this->FILE_H;
    }

    bishopMoves |= bishopMoves & ~this->RANK_8 & ~(this->NOT_WHITE_PIECES);

    std::cout << "Bishop Moves: " << bishopMoves << std::endl;

    return bishopMoves;
}

uint64_t Moves::getRookMoves(int const index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Rook Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    std::cout << BITBOARD << std::endl;

    int curFile = index % 8;

    uint64_t rookMoves = 0ULL;

    // Old
    // for (int i = 0; i < 4; i++) {
    //     uint64_t mask = 0ULL;
    //     uint64_t addCond = ~0ULL;
    //     int shift = 0;
    //     int count = 7;
    //
    //     switch (i) {
    //         case 0: {
    //             mask = (BITBOARD >> 8);
    //             shift = 8;
    //             break;
    //         }
    //         case 1: {
    //             mask = (BITBOARD << 8);
    //             shift = -8;
    //             break;
    //         }
    //         case 2: {
    //             mask = (BITBOARD >> 1);
    //             shift = 1;
    //             addCond = ~this->FILE_H;
    //             count = curFile+1;
    //             break;
    //         }
    //         case 3: {
    //             mask = (BITBOARD << 1);
    //             shift = -1;
    //             addCond = ~this->FILE_A;
    //             count = 8-curFile;
    //             break;
    //         }
    //     }
    //
    //     int const shiftIndex = shift;
    //     while ((~this->NOT_WHITE_PIECES & mask) != 0ULL && (std::abs(shift) < std::abs(shiftIndex)*count)) {
    //         rookMoves |= (mask & addCond);
    //
    //         shift += shiftIndex;
    //
    //         if (shiftIndex < 0)
    //             mask = (BITBOARD << std::abs(shift));
    //         else
    //             mask = (BITBOARD >> shift);
    //     }
    // }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_WHITE_PIECES & (BITBOARD >> (8 * i))) != 0ULL)
            break;

        rookMoves |= (BITBOARD >> (8 * i));
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_WHITE_PIECES & (BITBOARD << (8 * i))) != 0ULL)
            break;

        rookMoves |= (BITBOARD << (8 * i));
    }

    for (int i = 1; i < curFile+1; i++) {
        if (((this->NOT_WHITE_PIECES & (BITBOARD >> i)) != 0ULL))
            break;

        rookMoves |= (BITBOARD >> i) & ~this->FILE_H;
    }

    for (int i = 1; i < 8-curFile; i++) {
        if (((this->NOT_WHITE_PIECES & (BITBOARD << i)) != 0ULL))
            break;

        rookMoves |= (BITBOARD << i) & ~this->FILE_A;
    }

    return rookMoves;

}


uint64_t Moves::getQueenMoves(int const index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Queen Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    uint64_t queenMoves = 0ULL;

    queenMoves |= this->getBishopMoves(index, board, squares);
    queenMoves |= this->getRookMoves(index, board, squares);

    return queenMoves;
}

uint64_t Moves::getKingMoves(int index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Knight Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    // First Check if King is In Check
    // BITBOARD & this->AllOtherPieces
    uint64_t const knightMoves = this->getKnightMoves(index, board, squares);
    uint64_t const queenMoves = this->getQueenMoves(index, board, squares);
    uint64_t const pawnMoves = this->getPawnMoves(index, board, squares);

    uint64_t kingChecks = knightMoves | queenMoves | pawnMoves;

    return kingChecks;
}


void Moves::setWhiteP(uint64_t const board) {
    this->NOT_WHITE_PIECES = board;
}

void Moves::setBlackP(uint64_t const board) {
    this->BLACK_PIECES = board;
}

void Moves::setEmpty(uint64_t const board) {
    this->EMPTY = board;
}


