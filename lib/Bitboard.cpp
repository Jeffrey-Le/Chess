//
// Created by Jeffrey Vo Le on 5/14/24.
//
#include "../include/Bitboard.h"

Bitboard::Bitboard() {
    this->board = 0ULL;
    //std::cout << "In Bitboard: " << this->board << std::endl;
}

Bitboard::Bitboard(Square *squares) {
    this->board = 0ULL;

    //std::cout << "In Bitboard: " << this->board << std::endl;

}

Bitboard::~Bitboard() {
    //delete this->board;
}

void Bitboard::pawnMoves(float piece) {
    if (this->board == 0ULL || round(abs(piece)) == 1.0f)
    {
        std::cout << "ERROR, NO BOARD INITIALIZED OR WRONG PIECE" << std::endl;
        return;
    }

    // White
    if (piece > 0.0f)
    {
        if (this->board >> 7) {

        }
    }

    // Black
}

uint64_t Bitboard::convertToBitBoard(std::string const &Binary) {
    size_t offset = 0;
    if (Binary.at(0) == '0')
        return std::stoull(Binary, &offset, 2);
    else
        return std::stoull("1"+Binary.substr(2), &offset, 2)*2;
}

void Bitboard::updateBitboard(std::string const &Binary) {
    this->board += Bitboard::convertToBitBoard(Binary);
}

void Bitboard::displayBitboard() const{
    std::cout << uint64_t(this->board) << std::endl;
}

void Bitboard::setBitboard(uint64_t const &newBoard) {
    this->board = newBoard;
}


uint64_t Bitboard::useBitboard() const{
    return this->board;
}