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

    uint64_t const piecePos = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (piecePos);

    bool isNeg = (squares[index].usePiece() < 0.0f);

    uint64_t mask = 0ULL;

    // Check Capture Right
    uint64_t pawnMoves = this->OPPOSING_PIECES & ~this->FILE_A;

    if (isNeg)
        pawnMoves &= (BITBOARD << 7) & ~this->RANK_1;
    else
        pawnMoves &= (BITBOARD >> 7) & ~this->RANK_8;

    // Check Capture Left
    mask = this->OPPOSING_PIECES & ~this->FILE_H;

    if (isNeg)
        mask &= (BITBOARD << 9) & ~this->RANK_1;
    else
        mask &= (BITBOARD >> 9) & ~this->RANK_8;

    pawnMoves |= mask;

    // Move 1 Square
    // board >> 8  && EMPTY && ~RANK8
    mask = this->EMPTY;

    if (isNeg)
        mask &= (BITBOARD << 8) & ~this->RANK_1;
    else
        mask &= (BITBOARD >> 8) & ~this->RANK_8;

    pawnMoves |= mask;

    // Guaranteed to be a Pawn Derived Class
    Pawn* pawn = dynamic_cast<Pawn*>(squares[index].useOccupiedPiece());

    // Move 2 Square
    if (pawn->checkFirstMove()) {
        pawn->setFirstMove();

        mask = this->EMPTY & ~this->FILE_H;

        if (isNeg)
            mask &= (BITBOARD << 16) & ~this->RANK_1;
        else
            mask &= (BITBOARD >> 16) & ~this->RANK_8;
    }
    else
        mask = 0ULL;

    pawnMoves |= mask;


    // -- Promotions --

    // Promotion while Capture Right
    mask = this->OPPOSING_PIECES & ~this->FILE_A;

    if (isNeg)
        mask &= (BITBOARD << 7) & this->RANK_1;
    else
        mask &= (BITBOARD >> 7) & this->RANK_8;

    pawnMoves |= mask;

    // Promotion while Capture Left
    mask |=  this->OPPOSING_PIECES & ~this->FILE_H;

    if (isNeg)
        mask &= (BITBOARD << 9) & this->RANK_1;
    else
        mask &= (BITBOARD >> 9) & this->RANK_8;

    pawnMoves |= mask;

    // Promotion Move 1 Square
    mask |= this->EMPTY & ~this->FILE_H;

    if (isNeg)
        mask &= (BITBOARD << 8) & this->RANK_1;
    else
        mask &= (BITBOARD >> 8) & this->RANK_8;

    pawnMoves |= mask;

    return pawnMoves;
}

uint64_t Moves::getKnightMoves(int const index, Bitboard *&board, Square *&squares) const {
    std::cout << "In Knight Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    //int curFile = index % 8;

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

    knightMoves &= ~(this->NOT_PLAYER_PIECES);

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
        if ((this->NOT_PLAYER_PIECES & (BITBOARD >> (7 * i))) != 0ULL)
            break;

        if ((curFile + i) < 8 )
            bishopMoves |= (BITBOARD >> (7 * i)) & ~this->FILE_A;

    }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_PLAYER_PIECES & (BITBOARD >> (9 * i))) != 0ULL)
            break;

        if ((curFile - i) >= 0)
            bishopMoves |= (BITBOARD >> (9 * i)) & ~this->FILE_H;
    }

    bishopMoves |= bishopMoves & ~this->RANK_1;

    // Down Moves
    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_PLAYER_PIECES & (BITBOARD << (9 * i))) != 0ULL)
            break;

        if ((curFile + i) < 8)
            bishopMoves |= (BITBOARD << (9 * i)) & ~this->FILE_A;
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_PLAYER_PIECES & (BITBOARD << (7 * i))) != 0ULL)
            break;

        if ((curFile - i) >= 0)
            bishopMoves |= (BITBOARD << (7 * i)) & ~this->FILE_H;
    }

    bishopMoves |= bishopMoves & ~this->RANK_8 & ~(this->NOT_PLAYER_PIECES);

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
    //     while ((~this->NOT_PLAYER_PIECES & mask) != 0ULL && (std::abs(shift) < std::abs(shiftIndex)*count)) {
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
        if ((this->NOT_PLAYER_PIECES & (BITBOARD >> (8 * i))) != 0ULL)
            break;

        rookMoves |= (BITBOARD >> (8 * i));
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->NOT_PLAYER_PIECES & (BITBOARD << (8 * i))) != 0ULL)
            break;

        rookMoves |= (BITBOARD << (8 * i));
    }

    for (int i = 1; i < curFile+1; i++) {
        if (((this->NOT_PLAYER_PIECES & (BITBOARD >> i)) != 0ULL))
            break;

        rookMoves |= (BITBOARD >> i) & ~this->FILE_H;
    }

    for (int i = 1; i < 8-curFile; i++) {
        if (((this->NOT_PLAYER_PIECES & (BITBOARD << i)) != 0ULL))
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

uint64_t Moves::getKingMoves(int index, std::unordered_map<float, Bitboard*> bitBoards, Bitboard *&board, Square *&squares) const {
    std::cout << "In Knight Moves" << std::endl;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    // First Check if King is In Check
    // BITBOARD & this->AllOtherPieces
    uint64_t const knightMoves = this->getKnightMoves(index, board, squares);
    uint64_t const queenMoves = this->getQueenMoves(index, board, squares);
    uint64_t const pawnMoves = this->getPawnMoves(index, board, squares);

    uint64_t allPieces[] = {pawnMoves, knightMoves, queenMoves};

    uint64_t kingChecks = knightMoves | queenMoves | pawnMoves;

    std::cout << "King Checks: " << kingChecks << "\n";


    if ((pawnMoves & bitBoards[-1.0f]->useBitboard()) != 0ULL)
        return kingChecks;
    if ((knightMoves & bitBoards[-3.1f]->useBitboard()) != 0ULL)
        return kingChecks;
    if ((queenMoves & bitBoards[-9.0f]->useBitboard()) != 0ULL)
        return kingChecks;

    uint64_t kingMoves = 0ULL;

    // Directions: NW, N, NE, W, E, SW, S, SE

    uint64_t mask = 0ULL;

    // North East NE (Top-Left)
    mask |= (BITBOARD >> 9) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_1;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // North West NW (Top-Right)
    kingMoves |= (BITBOARD >> 7) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_1;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // North N (Top-Mid)
    kingMoves |= (BITBOARD >> 8) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_1;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // South East SE (Bottom-Left)
    kingMoves |= (BITBOARD << 7) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_8;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // South West SW (Bottom-Right)
    kingMoves |= (BITBOARD << 9) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_8;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // South S (Bottom-Mid)
    kingMoves |= (BITBOARD << 8) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_8;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // West W (Mid-Left)
    kingMoves |= (BITBOARD >> 1) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->FILE_H;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    // East E (Mid-Right)
    kingMoves |= (BITBOARD << 1) & ~this->NOT_PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->FILE_A;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves |= mask;

    //kingMoves = kingMoves & kingChecks;

    return kingMoves;
}

bool Moves::checkKingInCheck(uint64_t const otherPieces[], uint64_t mask) {
    for (int i = 0; i < 3; i++) {
        uint64_t temp = otherPieces[i];

        std::cout << (temp & mask) << std::endl;

        if ((temp & mask) != 0ULL)
            return true;
    }

    return false;
}


void Moves::setWhiteP(uint64_t const board) {
    this->NOT_PLAYER_PIECES = board;
}

void Moves::setBlackP(uint64_t const board) {
    this->OPPOSING_PIECES = board;
}

void Moves::setEmpty(uint64_t const board) {
    this->EMPTY = board;
}


