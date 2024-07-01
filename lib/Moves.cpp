//
// Created by Crolw on 5/31/2024.
//

#include "../include/Moves.h"

Moves::Moves() {

}

Moves::~Moves() {

}

void Moves::blackOrWhite(bool isNeg, uint64_t const BITBOARD, uint64_t &mask, int space) const {
    if (isNeg)
        mask &= (BITBOARD << space) & ~this->RANK_1;
    else
        mask &= (BITBOARD >> space) & ~this->RANK_8;
}


std::vector<uint64_t> Moves::getPawnMoves(int const index, Bitboard *&board, Square *&squares) const {
    // std::cout << "In Pawn Moves" << std::endl;

    uint64_t const piecePos = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (piecePos);

    bool isNeg = (squares[index].usePiece() < 0.0f);

    uint64_t mask = 0ULL;

    // Check Capture Right
    uint64_t pawnBasicMoves = 0ULL;
    uint64_t pawnCaptures = ~this->FILE_H;

    if (isNeg)
        pawnCaptures &= (BITBOARD << 7) & ~this->RANK_1;
    else
        pawnCaptures &= (BITBOARD >> 7) & ~this->RANK_8;

    // Check Capture Left
    mask = ~this->FILE_H;

    blackOrWhite(isNeg, BITBOARD, mask, 9);

    pawnCaptures |= mask;

    // Move 1 Square
    mask = this->EMPTY;

    blackOrWhite(isNeg, BITBOARD, mask, 8);

    pawnBasicMoves |= mask;

    // Guaranteed to be a Pawn Derived Class
    Pawn* pawn = dynamic_cast<Pawn*>(squares[index].useOccupiedPiece());

    // Move 2 Square
    if (pawn->checkFirstMove() && ((pawnBasicMoves & mask) != 0ULL)) {
        mask = this->EMPTY;

        blackOrWhite(isNeg, BITBOARD, mask, 16);
    }
    else
        mask = 0ULL;

    pawnBasicMoves |= mask;


    // -- Promotions --

    // Promotion while Capture Right
    mask = ~this->FILE_A;

    blackOrWhite(isNeg, BITBOARD, mask, 7);

    pawnCaptures |= mask;

    // Promotion while Capture Left
    mask = ~this->FILE_A;

    blackOrWhite(isNeg, BITBOARD, mask, 9);

    pawnCaptures |= mask;

    // Promotion Move 1 Square
    mask |= this->EMPTY & ~this->FILE_H;

    blackOrWhite(isNeg, BITBOARD, mask, 8);

    pawnBasicMoves |= mask;

    return std::vector<uint64_t>({pawnBasicMoves, pawnCaptures});
}

std::vector<uint64_t> Moves::getKnightMoves(int const index, Bitboard *&board, Square *&squares) const {
    // std::cout << "In Knight Moves" << std::endl;

    std::vector<uint64_t> knightMoves;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    //uint64_t knightMoves = 0ULL;

    if ((newSpaceMask & this->FILE_A) == 0ULL) {
        // Check Moves Right Up
        knightMoves.push_back(((BITBOARD >> 15) | (BITBOARD >> 6)) & ~this->FILE_AB & ~this->RANK_1);

        // Check Moves Right Down
        knightMoves.push_back(((BITBOARD << 17) | (BITBOARD << 10)) & ~this->FILE_AB & ~this->RANK_8);
    }
    else {
        // Check Moves Right Up
        knightMoves.push_back(((BITBOARD >> 15) | (BITBOARD >> 6)) & ~this->FILE_A & ~this->RANK_1);

        // Check Moves Right Down
        knightMoves.push_back(((BITBOARD << 17) | (BITBOARD << 10)) & ~this->FILE_A & ~this->RANK_8);
    }


    if ((newSpaceMask & this->FILE_H) == 0ULL) {
        // Check Moves Left Up
        knightMoves.push_back(((BITBOARD >> 17) | (BITBOARD >> 10)) & ~this->FILE_GH & ~this->RANK_1);

        // Check Moves Left Down
        knightMoves.push_back(((BITBOARD << 15) | (BITBOARD << 6)) & ~this->FILE_GH & ~this->RANK_8);
    }
    else {
        // Check Moves Left Up
        knightMoves.push_back(((BITBOARD >> 17) | (BITBOARD >> 10)) & ~this->FILE_H & ~this->RANK_1);

        // Check Moves Left Down
        knightMoves.push_back(((BITBOARD << 15) | (BITBOARD << 6)) & ~this->FILE_H & ~this->RANK_8);
    }

    for (auto &move: knightMoves)
        move &= ~(this->PLAYER_PIECES);

    return knightMoves;
}

std::vector<uint64_t> Moves::getBishopMoves(int const index, Bitboard *&board, Square *&squares) const {
    // std::cout << "In Bishop Moves" << std::endl;

    std::vector<uint64_t> bishopMoves = {0ULL, 0ULL, 0ULL, 0ULL};

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    int curFile = index % 8;

    // Check Right Moves

    // Check each other Ranks (7 Ranks) Up Moves
    for (int  i = 1; i < 7; i++) {
        if ((this->PLAYER_PIECES & (BITBOARD >> (7 * i))) != 0ULL)
            break;

        if ((curFile + i) < 8 )
            bishopMoves[0] |= (BITBOARD >> (7 * i)) & ~this->FILE_A;

        if ((this->OPPOSING_PIECES & (BITBOARD >> (7 * i))) != 0ULL)
            break;
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->PLAYER_PIECES & (BITBOARD >> (9 * i))) != 0ULL)
            break;

        if ((curFile - i) >= 0)
            bishopMoves[1] |= (BITBOARD >> (9 * i)) & ~this->FILE_H;

        if ((this->OPPOSING_PIECES & (BITBOARD >> (9 * i))) != 0ULL)
            break;
    }

    // Down Moves
    for (int  i = 1; i < 7; i++) {
        if ((this->PLAYER_PIECES & (BITBOARD << (9 * i))) != 0ULL)
            break;

        if ((curFile + i) < 8)
             bishopMoves[2] |= (BITBOARD << (9 * i)) & ~this->FILE_A;

        if ((this->OPPOSING_PIECES & (BITBOARD << (9 * i))) != 0ULL)
            break;
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->PLAYER_PIECES & (BITBOARD << (7 * i))) != 0ULL)
            break;

        if ((curFile - i) >= 0)
             bishopMoves[3] |= (BITBOARD << (7 * i)) & ~this->FILE_H;

        if ((this->OPPOSING_PIECES & (BITBOARD << (7 * i))) != 0ULL)
            break;
    }

    bishopMoves[0] &= ~this->RANK_1;
    bishopMoves[1] &= ~this->RANK_1;
    bishopMoves[2] &= ~this->RANK_8 & ~(this->PLAYER_PIECES);
    bishopMoves[3] &= ~this->RANK_8 & ~(this->PLAYER_PIECES);

    //bishopMoves |= bishopMoves & ~this->RANK_8 & ~(this->PLAYER_PIECES);

    return bishopMoves;
}

std::vector<uint64_t> Moves::getRookMoves(int const index, Bitboard *&board, Square *&squares) const {
    // std::cout << "In Rook Moves" << std::endl;

    std::vector<uint64_t> rookMoves = {0ULL, 0ULL, 0ULL, 0ULL};

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    int curFile = index % 8;

    for (int  i = 1; i < 7; i++) {
        if ((this->PLAYER_PIECES & (BITBOARD >> (8 * i))) != 0ULL)
            break;


        rookMoves[0] |= (BITBOARD >> (8 * i));

        if ((this->OPPOSING_PIECES & (BITBOARD >> (8 * i))) != 0ULL)
            break;
    }

    for (int  i = 1; i < 7; i++) {
        if ((this->PLAYER_PIECES & (BITBOARD << (8 * i))) != 0ULL)
            break;

        rookMoves[1] |= (BITBOARD << (8 * i));

        if ((this->OPPOSING_PIECES & (BITBOARD << (8 * i))) != 0ULL)
            break;
    }

    for (int i = 1; i < curFile+1; i++) {
        if (((this->PLAYER_PIECES & (BITBOARD >> i)) != 0ULL))
            break;

        rookMoves[2] |= (BITBOARD >> i) & ~this->FILE_H;

        if (((this->OPPOSING_PIECES & (BITBOARD >> i)) != 0ULL))
            break;
    }

    for (int i = 1; i < 8-curFile; i++) {
        if (((this->PLAYER_PIECES & (BITBOARD << i)) != 0ULL))
            break;

        rookMoves[3] |= (BITBOARD << i) & ~this->FILE_A;

        if (((this->OPPOSING_PIECES & (BITBOARD << i)) != 0ULL))
            break;
    }

    return rookMoves;
}


std::vector<uint64_t> Moves::getQueenMoves(int const index, Bitboard *&board, Square *&squares) const {
    //std::cout << "In Queen Moves" << std::endl;

    std::vector<uint64_t> queenMoves;

    std::vector<uint64_t> bishopMoves = this->getBishopMoves(index, board, squares);
    std::vector<uint64_t> rookMoves =  this->getRookMoves(index, board, squares);

    queenMoves.insert(queenMoves.end(), std::make_move_iterator(bishopMoves.begin()), std::make_move_iterator(bishopMoves.end()));
    queenMoves.insert(queenMoves.end(), std::make_move_iterator(rookMoves.begin()), std::make_move_iterator(rookMoves.end()));

    return queenMoves;
}

std::vector<uint64_t> Moves::getKingMoves(int const index, std::unordered_map<float, Bitboard*> bitBoards, Bitboard *&board, Square *&squares) {
    // std::cout << "In King Moves" << std::endl;

    std::vector<uint64_t> kingMoves;

    uint64_t const newSpaceMask = 1ULL << index;

    uint64_t const BITBOARD = board->useBitboard() & (newSpaceMask);

    float multiplier = (squares[index].usePiece() > 0.0f) ? 1.0f : -1.0f;

    // Swap Player Pieces to check For Possible Moves of Opposing Pieces
    uint64_t tempPlayerP = this->PLAYER_PIECES;
    this->setPlayerP(this->OPPOSING_PIECES);
    this->setOpposingP(tempPlayerP);

    uint64_t pawnMoves = 0ULL;
    uint64_t knightMoves = 0ULL;
    uint64_t bishopMoves = 0ULL;
    uint64_t rookMoves = 0ULL;
    uint64_t queenMoves = 0ULL;

    // Loop Through Opposing Player Board
    uint64_t opposingBoard = this->PLAYER_PIECES;
    int curPieceIndex = 0;

    while (opposingBoard != 0ULL) { // If it Reaches 0, stop looping early -> Means It's checked all pieces on board already
        // Pawn
        uint64_t pieceBoard = (bitBoards[-1.0f * multiplier]->useBitboard() >> curPieceIndex);

        if ((opposingBoard & pieceBoard) & 1ULL)
            pawnMoves |= this->getPawnMoves(curPieceIndex, bitBoards[-1.0f * multiplier], squares)[1];

        // Knight
        pieceBoard = (bitBoards[-3.1f * multiplier]->useBitboard() >> curPieceIndex);

        if ((opposingBoard & pieceBoard) & 1ULL) {
            std::vector<uint64_t> allKnightMoves = this->getKnightMoves(curPieceIndex, bitBoards[-3.1f * multiplier], squares);

            for (auto &move: allKnightMoves)
                knightMoves |= move;
        }

        // Bishop
        pieceBoard = (bitBoards[-3.2f * multiplier]->useBitboard() >> curPieceIndex);

        if ((opposingBoard & pieceBoard) & 1ULL) {
            std::vector<uint64_t> allBishopMoves = this->getBishopMoves(curPieceIndex, bitBoards[-3.2f * multiplier], squares);

            for (auto &move: allBishopMoves)
                bishopMoves |= move;
        }

        // Rook
        pieceBoard = (bitBoards[-5.0f * multiplier]->useBitboard() >> curPieceIndex);

        if ((opposingBoard & pieceBoard) & 1ULL) {
           std::vector<uint64_t> allRookMoves =this->getRookMoves(curPieceIndex, bitBoards[-5.0f * multiplier], squares);

            for (auto &move: allRookMoves)
                rookMoves |= move;
        }

        // Queen
        pieceBoard = (bitBoards[-9.0f * multiplier]->useBitboard() >> curPieceIndex);

        if ((opposingBoard & pieceBoard) & 1ULL) {
            std::vector<uint64_t> allQueenMoves = this->getQueenMoves(curPieceIndex, bitBoards[-9.0f * multiplier], squares);

            for (auto &move: allQueenMoves)
                queenMoves |= move;
        }

        opposingBoard >>= 1;
        curPieceIndex++;
    }

    std::vector<uint64_t> allPieces = {pawnMoves, knightMoves, bishopMoves, rookMoves, queenMoves};

    // Swap Back
    tempPlayerP = this->PLAYER_PIECES;
    this->setPlayerP(this->OPPOSING_PIECES);
    this->setOpposingP(tempPlayerP);



    // Directions: NW, N, NE, W, E, SW, S, SE

    uint64_t mask = 0ULL;

    // North East NE (Top-Left)
    // North West NW (Top-Right)
    // North N (Top-Mid)
    for (int i = 7; i < 10; i++) {
        mask = (BITBOARD >> i) & ~this->PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_1;
        if (!checkKingInCheck(allPieces, mask))
            kingMoves.push_back(mask);
    }

    // South East SE (Bottom-Left)
    // South West SW (Bottom-Right)
    // South S (Bottom-Mid)
    for (int i = 7; i < 10; i++) {
        mask = (BITBOARD << i) & ~this->PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->RANK_8;
        if (!checkKingInCheck(allPieces, mask))
            kingMoves.push_back(mask);
    }

    // West W (Mid-Left)
    mask = (BITBOARD >> 1) & ~this->PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->FILE_H;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves.push_back(mask);

    // East E (Mid-Right)
    mask = (BITBOARD << 1) & ~this->PLAYER_PIECES & (this->OPPOSING_PIECES | this->EMPTY) & ~this->FILE_A;
    if (!checkKingInCheck(allPieces, mask))
        kingMoves.push_back(mask);

    return kingMoves;
}

bool Moves::checkKingInCheck(std::vector<uint64_t> const &otherPieces, uint64_t mask) {
    if (std::any_of(otherPieces.begin(), otherPieces.end(), [&mask](uint64_t piece) {return (piece & mask) != 0ULL;}))
        return true;

    return false;
}


void Moves::setPlayerP(uint64_t const board) {
    this->PLAYER_PIECES = board;
}

void Moves::setOpposingP(uint64_t const board) {
    this->OPPOSING_PIECES = board;
}

void Moves::setEmpty(uint64_t const board) {
    this->EMPTY = board;
}

uint64_t Moves::useOpposingP() const {
    return this->OPPOSING_PIECES;
}


