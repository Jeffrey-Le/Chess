//
// Created by Jeffrey Vo Le on 5/14/24.
//
#include "../include/Bitboard.h"

Bitboard::Bitboard() {
    this->board = 0ULL;
}

Bitboard::Bitboard(Square *squares) {
    this->board = 0ULL;

    std::cout << "In Bitboard: " << this->board << std::endl;

    std::string Binary;

    for (int i = 0; i < 64; i++)
    {
        Binary  = "0000000000000000000000000000000000000000000000000000000000000000";
        Binary = Binary.substr(i+1)+"1"+Binary.substr(0, i);
        float pieceVal = squares[i].usePiece();

        switch (int64_t(floor(pieceVal))) {
            case 1:
                std::cout << "1" << std::endl;
                this->board  += this->convertToBitBoard(Binary);
                break;
            case -1:
                std::cout << "-1" << std::endl;
                this->board += this->convertToBitBoard(Binary);
                break;
            case 3:
                std::cout << "3" << std::endl;
                if (pieceVal == 3.1f)
                    this->board += this->convertToBitBoard(Binary);
                if (pieceVal == 3.2f)
                    this->board += this->convertToBitBoard(Binary);
                break;
            case -3:
                std::cout << "-3" << std::endl;
                if (pieceVal == -3.1f)
                    this->board += this->convertToBitBoard(Binary);
                if (pieceVal == -3.2f)
                    this->board += this->convertToBitBoard(Binary);
                break;
            case 5:
                std::cout << "5" << std::endl;
                this->board += this->convertToBitBoard(Binary);
                break;
            case -5:
                std::cout << "-5" << std::endl;
                this->board += this->convertToBitBoard(Binary);
                break;
            case 9:
                std::cout << "9" << std::endl;
                this->board += this->convertToBitBoard(Binary);
                break;
            case -9:
                std::cout << "-9" << std::endl;
                this->board += this->convertToBitBoard(Binary);
                break;
            default:
                std::cout << "default" << std::endl;
                if (pieceVal == 0.1f)
                    this->board += this->convertToBitBoard(Binary);
                if (pieceVal == -0.1f)
                    this->board += this->convertToBitBoard(Binary);
        }

    }
    std::cout << Binary << std::endl;
}

Bitboard::~Bitboard() {
    //delete this->board;
}

uint64_t  Bitboard::convertToBitBoard(std::string Binary) {
    size_t offset = 0;
    if (Binary.at(0) == '0')
        return std::stoull(Binary, &offset, 2);
    else
        return std::stoull("1"+Binary.substr(2), &offset, 2)*2;
}

void Bitboard::displayBitboard() {
    std::cout << uint64_t(this->board) << std::endl;
}