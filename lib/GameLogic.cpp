//
// Created by Jeffrey Vo Le on 5/16/24.
//
#include "../include/GameLogic.h"

GameLogic::GameLogic() {
    this->players = new Player[2];

    this->curBoard = nullptr;
    this->curBitboard = new Bitboard();

    this->whitePawn = new Bitboard();
    this->whiteRook = new Bitboard();
    this->whiteKnight = new Bitboard();
    this->whiteBishop = new Bitboard();
    this->whiteQueen = new Bitboard();
    this->whiteKing = new Bitboard();

    this->blackPawn = new Bitboard();
    this->blackRook = new Bitboard();
    this->blackKnight = new Bitboard();
    this->blackBishop = new Bitboard();
    this->blackQueen = new Bitboard();
    this->blackKing = new Bitboard();
}

GameLogic::GameLogic(Board &board) {
    this->players = new Player[2];

    this->curBoard = &board;
    this->curBitboard = new Bitboard();

    // Initialize White Bitboards
    this->whitePawn = new Bitboard();
    this->whiteRook = new Bitboard();
    this->whiteKnight = new Bitboard();
    this->whiteBishop = new Bitboard();
    this->whiteQueen = new Bitboard();
    this->whiteKing = new Bitboard();

    // Initialize Black Bitboards
    this->blackPawn = new Bitboard();
    this->blackRook = new Bitboard();
    this->blackKnight = new Bitboard();
    this->blackBishop = new Bitboard();
    this->blackQueen = new Bitboard();
    this->blackKing = new Bitboard();

    this->setIntialBoard();
}

GameLogic::~GameLogic() {
    delete this->curBoard;

    // Free Piece Bitboard memory space
    delete this->whitePawn;
    delete this->whiteRook;
    delete this->whiteKnight;
    delete this->whiteBishop;
    delete this->whiteQueen;
    delete this->whiteKing;
    delete this->blackPawn;
    delete this->blackRook;
    delete this->blackKnight;
    delete this->blackBishop;
    delete this->blackQueen;
    delete this->blackKing;
}

void GameLogic::setIntialBoard() const {

    Square *squares = this->curBoard->useBoard();

    static std::string Binary;

    for (int i = 0; i < 64; i++)
    {
        Binary  = "0000000000000000000000000000000000000000000000000000000000000000";
        Binary = Binary.substr(i+1)+"1"+Binary.substr(0, i);
        float pieceVal = squares[i].usePiece();

        switch (int64_t(round(pieceVal))) {
            case 1:
                std::cout << "1" << std::endl;
                this->whitePawn->updateBitboard(Binary);
                squares[i].setOccupiedPiece(new Pawn('w'));
                break;
            case -1:
                std::cout << "-1" << std::endl;
                this->blackPawn->updateBitboard(Binary);
                squares[i].setOccupiedPiece(new Pawn('b'));
                break;
            case 3:
                std::cout << "3" << std::endl;
                if (pieceVal == 3.1f) {
                    this->whiteKnight->updateBitboard(Binary);
                    squares[i].setOccupiedPiece(new Knight('w'));
                }
                if (pieceVal == 3.2f) {
                    this->whiteBishop->updateBitboard(Binary);

                }
                break;
            case -3:
                std::cout << "-3" << std::endl;
                if (pieceVal == -3.1f) {
                    this->blackKnight->updateBitboard(Binary);
                    squares[i].setOccupiedPiece(new Knight('b'));
                }
                if (pieceVal == -3.2f)
                    this->blackBishop->updateBitboard(Binary);
                break;
            case 5:
                std::cout << "5" << std::endl;
                this->whiteRook->updateBitboard(Binary);
                break;
            case -5:
                std::cout << "-5" << std::endl;
                this->blackRook->updateBitboard(Binary);
                break;
            case 9:
                std::cout << "9" << std::endl;
                this->whiteQueen->updateBitboard(Binary);
                break;
            case -9:
                std::cout << "-9" << std::endl;
                this->blackQueen->updateBitboard(Binary);
                break;
            default:
                std::cout << "default" << std::endl;
                if (pieceVal == 0.1f)
                    this->whiteKing->updateBitboard(Binary);
                if (pieceVal == -0.1f)
                    this->blackKing->updateBitboard(Binary);
        }
    this->curBitboard->updateBitboard(Binary); // Updates Game Board State
    }
}

void GameLogic::displayBitboard(char const name, char const color) const {

    if (color == 'w')
    {
    switch (std::tolower(name)) {
        case 'p':
            std::cout << "WhitePawn Bitboard:" << std::endl;
            this->whitePawn->displayBitboard();
            break;
        case 'n':
            std::cout << "WhiteKnight Bitboard:" << std::endl;
            this->whiteKnight->displayBitboard();
            break;
        case 'b':
            std::cout << "WhiteBishop Bitboard:" << std::endl;
            this->whiteBishop->displayBitboard();
            break;
        case 'r':
            std::cout << "WhiteRook Bitboard:" << std::endl;
            this->whiteRook->displayBitboard();
            break;
        case 'q':
            std::cout << "WhiteQueen Bitboard:" << std::endl;
            this->whiteQueen->displayBitboard();
            break;
        case 'k':
            std::cout << "WhiteKing Bitboard:" << std::endl;
            this->whiteKing->displayBitboard();
            break;
        default:
            std::cout << "NO PIECE CHARACTER INPUTTED" << std::endl; // Error
        }
    }
    if (color == 'b') {
        switch (std::tolower(name)) {
            case 'p':
                std::cout << "BlackPawn Bitboard:" << std::endl;
                this->blackPawn->displayBitboard();
                break;
            case 'n':
                std::cout << "BlackKnight Bitboard:" << std::endl;
                this->blackKnight->displayBitboard();
                break;
            case 'b':
                std::cout << "BlackBishop Bitboard:" << std::endl;
                this->blackBishop->displayBitboard();
                break;
            case 'r':
                std::cout << "BlackRook Bitboard:" << std::endl;
                this->blackRook->displayBitboard();
                break;
            case 'q':
                std::cout << "BlackQueen Bitboard:" << std::endl;
                this->blackQueen->displayBitboard();
                break;
            case 'k':
                std::cout << "BlackKing Bitboard" << std::endl;
                this->blackKing->displayBitboard();
                break;
            default:
                std::cout << "NO PIECE CHARACTER INPUTTED" << std::endl; // Error
        }
    }

    if (color != 'w' && color != 'b')
        std::cout << "ERROR, NO COLOR PROVIDED" << std::endl;
}

void GameLogic::revertBitboard() const{
    // Check if Board Exists
    if (this->curBoard == nullptr)
    {
        std::cout << "NO BOARD HAS BEEN SET" << std::endl;
        return;
    }

    Square *squares = this->curBoard->useBoard();

    for (int i = 0; i < 64; i++)
        squares[i].changePiece(0.0f);

    // Reverts Bitboard into Board
    for (int i = 0; i < 64; i++)
    {
        if ((this->whitePawn->useBitboard() >> i) & 1) squares[i].changePiece(1.0f);
        if ((this->whiteKnight->useBitboard() >> i) & 1) squares[i].changePiece(3.1f);
        if ((this->whiteBishop->useBitboard() >> i) & 1) squares[i].changePiece(3.2f);
        if ((this->whiteRook->useBitboard() >> i) & 1) squares[i].changePiece(5.0f);
        if ((this->whiteQueen->useBitboard() >> i) & 1) squares[i].changePiece(9.0f);
        if ((this->whiteKing->useBitboard() >> i) & 1) squares[i].changePiece(0.1f);
        if ((this->blackPawn->useBitboard() >> i) & 1) squares[i].changePiece(-1.0f);
        if ((this->blackKnight->useBitboard() >> i) & 1) squares[i].changePiece(-3.1f);
        if ((this->blackBishop->useBitboard() >> i) & 1) squares[i].changePiece(-3.2f);
        if ((this->blackRook->useBitboard() >> i) & 1) squares[i].changePiece(-5.0f);
        if ((this->blackQueen->useBitboard() >> i) & 1) squares[i].changePiece(-9.0f);
        if ((this->blackKing->useBitboard() >> i) & 1) squares[i].changePiece(-0.1f);
    }

//    std::cout << "Old Board" << std::endl;
//    this->curBoard->displayBoard();
//
//    this->curBoard->setSquares(squares);
//
//    std::cout << "New Board" << std::endl;
//    this->curBoard->displayBoard();
}

void GameLogic::getPossibleMoves(int const index) {
    Moves moves;

    Square *squares = this->curBoard->useBoard();

    std::string const Binary = "000ULL";

    float const pieceVal = squares[index].usePiece();

    if (std::tolower(this->players[0].getColor().at(0)) == 'w') {
        uint64_t notWP = bitwiseOr(this->whitePawn, this->whiteBishop);

        notWP = bitwiseOr(notWP, this->whiteKing->useBitboard());
        notWP = bitwiseOr(notWP, this->whiteKnight->useBitboard());
        notWP = bitwiseOr(notWP, this->whiteQueen->useBitboard());
        notWP = bitwiseOr(notWP, this->whiteRook->useBitboard());
        notWP = bitwiseOr(notWP, this->blackKing->useBitboard());
        moves.setWhiteP(notWP);

        uint64_t BlP = bitwiseOr(this->blackBishop, this->blackQueen);
        BlP = bitwiseOr(BlP, this->blackKnight->useBitboard());
        BlP = bitwiseOr(BlP, this->blackPawn->useBitboard());
        BlP = bitwiseOr(BlP, this->blackRook->useBitboard());
        moves.setBlackP(BlP);

        uint64_t const empty = ~bitwiseOr(notWP, BlP);
        moves.setEmpty(empty);
    }
    if (std::tolower(this->players[0].getColor().at(0)) == 'b') {
        uint64_t notBP = bitwiseOr(this->whitePawn, this->whiteBishop);

        notBP = bitwiseOr(notBP, this->whiteKing->useBitboard());
        notBP = bitwiseOr(notBP, this->whiteKnight->useBitboard());
        notBP = bitwiseOr(notBP, this->whiteQueen->useBitboard());
        notBP = bitwiseOr(notBP, this->whiteRook->useBitboard());
        moves.setWhiteP(notBP);

        uint64_t BlP = bitwiseOr(this->blackBishop, this->blackQueen);
        BlP = bitwiseOr(BlP, this->blackKnight->useBitboard());
        BlP = bitwiseOr(BlP, this->blackPawn->useBitboard());
        BlP = bitwiseOr(BlP, this->blackRook->useBitboard());
        moves.setBlackP(BlP);

        uint64_t empty = bitwiseOr(notBP, BlP);
        empty = bitwiseOr(empty, this->blackKing->useBitboard());
        empty = ~empty;
        moves.setEmpty(empty);
    }

    switch (int64_t(std::round(pieceVal))) {
        case 1:
        {
            std::cout << "1" << std::endl;
            // uint64_t const possibeCapture = this->bitwiseOr(this->whitePawn->useBitboard() >> 7, this->whitePawn->useBitboard() >> 9);
            // if (this->bitwiseAnd(possibeCapture, this->curBitboard->useBitboard()) != 0ULL)
            //     // REturn Bitboard instead and revert to display on visual board
            //     std::cout << "Can Capture" << std::endl;
            moves.getPawnMoves(1, this->whitePawn,squares, index);
            break;
        }
        case -1:
            std::cout << "-1" << std::endl;
            this->blackPawn->updateBitboard(Binary);
            break;
        case 3:
            std::cout << "3" << std::endl;
            if (pieceVal == 3.1f) {
                moves.getPawnMoves(1, this->whitePawn,squares, index);
                this->whiteKnight->updateBitboard(Binary);
            }
            if (pieceVal == 3.2f)
                this->whiteBishop->updateBitboard(Binary);
            break;
        case -3:
            std::cout << "-3" << std::endl;
            if (pieceVal == -3.1f)
                this->blackKnight->updateBitboard(Binary);
            if (pieceVal == -3.2f)
                this->blackBishop->updateBitboard(Binary);
            break;
        case 5:
            std::cout << "5" << std::endl;
            this->whiteRook->updateBitboard(Binary);
            break;
        case -5:
            std::cout << "-5" << std::endl;
            this->blackRook->updateBitboard(Binary);
            break;
        case 9:
            std::cout << "9" << std::endl;
            this->whiteQueen->updateBitboard(Binary);
            break;
        case -9:
            std::cout << "-9" << std::endl;
            this->blackQueen->updateBitboard(Binary);
            break;
        default:
            std::cout << "default" << std::endl;
            if (pieceVal == 0.1f)
                this->whiteKing->updateBitboard(Binary);
            if (pieceVal == -0.1f)
                this->blackKing->updateBitboard(Binary);
    }

}

void GameLogic::updateMoves(int index) {
    auto *squares = this->curBoard->useBoard();


}


uint64_t GameLogic::bitwiseAnd(Bitboard *&board1, Bitboard *&board2) {
    return board1->useBitboard() & board2->useBitboard();
}

uint64_t GameLogic::bitwiseOr(Bitboard *&board1, Bitboard *&board2) {
    return board1->useBitboard() | board2->useBitboard();
}

uint64_t GameLogic::bitwiseAnd(uint64_t const board1, uint64_t const board2) {
    return board1 & board2;
}

uint64_t GameLogic::bitwiseOr(uint64_t const board1, uint64_t const board2) {
    return board1 | board2;
}