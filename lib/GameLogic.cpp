//
// Created by Jeffrey Vo Le on 5/16/24.
//
#include "../include/GameLogic.h"

#include <memory>


GameLogic::GameLogic() {
    this->players = new Player[2];

    this->curBoard = nullptr;
    this->curBitboard = new Bitboard();
    this->possibleMoves = new Bitboard();

    float values[] = {1.0, 3.1, 3.2, 5.0, 9.0, 0.1};

    for (auto i = 0; i < 6; i++) {
        this->bitBoards[values[i]] = new Bitboard();
        this->bitBoards[-values[i]] = new Bitboard();
    }

}

GameLogic::GameLogic(Board &board) {
    this->players = new Player[2];

    this->curBoard = &board;
    this->curBitboard = new Bitboard();

    this->possibleMoves = new Bitboard();

    float values[] = {1.0, 3.1, 3.2, 5.0, 9.0, 0.1};

    for (auto i = 0; i < 6; i++) {
        this->bitBoards[values[i]] = new Bitboard();
        this->bitBoards[-values[i]] = new Bitboard();
    }

    this->setIntialBoard();
}

GameLogic::~GameLogic() {
    delete this->curBoard;

    // Free Piece Bitboard memory space
    for (auto & bitBoard : this->bitBoards)
        delete bitBoard.second;

    this->bitBoards.clear();
}

void GameLogic::setIntialBoard() {
    // std::unordered_map<float, std::function<std::shared_ptr<Piece>()>> PieceInfo = {
    //     {1.0f, []() -> std::shared_ptr<Piece> { return std::make_shared<Pawn>('w');}},
    //     {3.1f, []() -> std::shared_ptr<Piece> { return std::make_shared<Knight>('w');}},
    //     {3.2f, []() -> std::shared_ptr<Piece> { return std::make_shared<Bishop>('w');}},
    //     {5.0f, []() -> std::shared_ptr<Piece> { return std::make_shared<Rook>('w');}},
    //     { 9.0f, []() -> std::shared_ptr<Piece> { return std::make_shared<Queen>('w');}},
    //     {0.1f, []() -> std::shared_ptr<Piece> { return std::make_shared<King>('w');}},
    //     {-1.0f, []() -> std::shared_ptr<Piece> { return std::make_shared<Pawn>('b');}},
    //     {-3.1f, []() -> std::shared_ptr<Piece> { return std::make_shared<Knight>('b');}},
    //     {-3.2f, []() -> std::shared_ptr<Piece> { return std::make_shared<Bishop>('b');}},
    //     {-5.0f, []() -> std::shared_ptr<Piece> { return std::make_shared<Rook>('b');}},
    //     { -9.0f, []() -> std::shared_ptr<Piece> { return std::make_shared<Queen>('b');}},
    //     {-0.1f, []() -> std::shared_ptr<Piece> { return std::make_shared<King>('b');}},
    // };

    Square *squares = this->curBoard->useBoard();

    static std::string Binary;

    for (int i = 0; i < 64; i++)
    {
        Binary  = "0000000000000000000000000000000000000000000000000000000000000000";
        Binary = Binary.substr(i+1)+"1"+Binary.substr(0, i);
        float const pieceVal = squares[i].usePiece();


        if (pieceVal != 0.0f) {
            std::unordered_map<float, Piece*> PieceInfo = {
                {1.0f, new Pawn('w')},
                {3.1f, new Knight('w')},
                {3.2f, new Bishop('w')},
                {5.0f, new Rook('w')},
                { 9.0f, new Queen('w')},
                {0.1f, new King('w')},
                {-1.0f, new Pawn('b')},
                {-3.1f, new Knight('b')},
                {-3.2f, new Bishop('b')},
                {-5.0f, new Rook('b')},
                { -9.0f, new Queen('b')},
                {-0.1f, new King('b')},
            };

            std::cout << "PieceVal: " << pieceVal << std::endl;

            this->bitBoards[pieceVal]->updateBitboard(Binary);

            squares[i].setOccupiedPiece(PieceInfo[pieceVal]);

            this->curBitboard->updateBitboard(Binary);
        }
    }
}

void GameLogic::displayBitboard(char const name, char const color) {
    std::unordered_map<std::string, float> PieceInfo = {
        {"pw", 1.0f},
        {"nw", 3.1f},
        {"bw", 3.2f},
        {"rw", 5.0f},
        {"qw", 9.0f},
        {"kw", 0.1f},
        {"pb", -1.0f},
        {"nb", -3.1f},
        {"bb", -3.2f},
        {"rb", -5.0f},
        {"qb", -9.0f},
        {"kb", -0.1f}
    };

    if (color == 'w') {
        std::string key = "";
        key += std::tolower(name);
        key += 'w';

        float const pieceVal = PieceInfo[key];

        std::cout << key << std::endl;

        this->bitBoards[pieceVal]->displayBitboard();
    }

    if (color == 'b') {
        std::string key = "";
        key += std::tolower(name);
        key += 'b';

        float const pieceVal = PieceInfo[key];

        this->bitBoards[pieceVal]->displayBitboard();
    }

    if (color != 'w' && color != 'b')
        std::cout << "ERROR, NO COLOR PROVIDED" << std::endl;
}

void GameLogic::revertBitboard(){
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
        if ((this->bitBoards[1.0f]->useBitboard() >> i) & 1) squares[i].changePiece(1.0f);
        if ((this->bitBoards[3.1f]->useBitboard() >> i) & 1) squares[i].changePiece(3.1f);
        if ((this->bitBoards[3.2f]->useBitboard() >> i) & 1) squares[i].changePiece(3.2f);
        if ((this->bitBoards[5.0f]->useBitboard() >> i) & 1) squares[i].changePiece(5.0f);
        if ((this->bitBoards[9.0f]->useBitboard() >> i) & 1) squares[i].changePiece(9.0f);
        if ((this->bitBoards[0.1f]->useBitboard() >> i) & 1) squares[i].changePiece(0.1f);
        if ((this->bitBoards[-1.0f]->useBitboard() >> i) & 1) squares[i].changePiece(-1.0f);
        if ((this->bitBoards[-3.1f]->useBitboard() >> i) & 1) squares[i].changePiece(-3.1f);
        if ((this->bitBoards[-3.2f]->useBitboard() >> i) & 1) squares[i].changePiece(-3.2f);
        if ((this->bitBoards[-5.0f]->useBitboard() >> i) & 1) squares[i].changePiece(-5.0f);
        if ((this->bitBoards[-9.0f]->useBitboard() >> i) & 1) squares[i].changePiece(-9.0f);
        if ((this->bitBoards[-0.1f]->useBitboard() >> i) & 1) squares[i].changePiece(-0.1f);
    }

//    std::cout << "Old Board" << std::endl;
//    this->curBoard->displayBoard();
//
//    this->curBoard->setSquares(squares);
//
//    std::cout << "New Board" << std::endl;
//    this->curBoard->displayBoard();
}

bool GameLogic::compareNeg(float x, float y) {
    if (y > 0.0f) {
        return (x > y);
    }
    return (x <= y);
}

float GameLogic::operator<=(float &other) {
    if (other > 0.0f)
        return (other < 0);

    return (other > 0);
}

void GameLogic::getPossibleMoves(int const index) {
    Moves moves;

    Square *squares = this->curBoard->useBoard();

    std::string const Binary = "0ULL";

    float const pieceVal = squares[index].usePiece();

    int multiplier = 1; // w = 1, b = -1

    uint64_t notPlayerP = this->bitBoards[pieceVal]->useBitboard();

    if (std::tolower(this->players[0].getColor().at(0)) == 'w') {
        for (auto &bitBoard: this->bitBoards) {
            if (bitBoard.first > 0.0f)
                notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
        }
    }
    else {
        for (auto &bitBoard: this->bitBoards) {
            if (bitBoard.first < 0.0f)
                notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
        }

        multiplier = -1;
    }


    notPlayerP = bitwiseOr(notPlayerP, this->bitBoards[-0.1f * float(multiplier)]->useBitboard());

    moves.setWhiteP(notPlayerP);

    uint64_t opposingP = this->bitBoards[-1.0f * float(multiplier)]->useBitboard();

    for (auto & bitBoard : this->bitBoards) {
        if (bitBoard.first == (-1.0f * float(multiplier)) || bitBoard.first == (-0.1f * float(multiplier)))
            continue;

        if (multiplier > 0) {
            if (bitBoard.first < 0.0f)
                notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
        }
        else {
            if (bitBoard.first > 0.0f)
                notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
        }
    }

    std::cout << notPlayerP << std::endl;

    moves.setBlackP(opposingP);

    uint64_t const empty = ~bitwiseOr(notPlayerP, opposingP);
    moves.setEmpty(empty);
//
//    if (std::tolower(this->players[0].getColor().at(0)) == 'w') {
//
//        for (auto & bitBoard : this->bitBoards) {
//            if (bitBoard.first > 0.0f)
//                notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
//        }
//
//        notPlayerP = bitwiseOr(notPlayerP, this->bitBoards[-0.1f]->useBitboard());
//
//        moves.setWhiteP(notPlayerP);
//
//        uint64_t BlP = this->bitBoards[-1.0f]->useBitboard();
//
//        for (auto & bitBoard : this->bitBoards) {
//            if (bitBoard.first == -1.0f || bitBoard.first == -0.1f)
//                continue;
//
//            if (bitBoard.first < 0.0f)
//                notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
//        }
//
//        moves.setBlackP(BlP);
//
//        uint64_t const empty = ~bitwiseOr(notPlayerP, BlP);
//        moves.setEmpty(empty);
//    }
//    else {
//        uint64_t notWP = this->bitBoards[pieceVal]->useBitboard();
//
//        for (auto & bitBoard : this->bitBoards) {
//            if (bitBoard.first > 0.0f)
//                notWP = bitwiseOr(notWP, bitBoard.second->useBitboard());
//        }
//
//        notWP = bitwiseOr(notWP, this->bitBoards[-0.1f]->useBitboard());
//
//        moves.setWhiteP(notWP);
//
//        uint64_t BlP = this->bitBoards[-1.0f]->useBitboard();
//
//        for (auto & bitBoard : this->bitBoards) {
//            if (bitBoard.first == -1.0f || bitBoard.first == -0.1f)
//                continue;
//
//            if (bitBoard.first < 0.0f)
//                notWP = bitwiseOr(notWP, bitBoard.second->useBitboard());
//        }
//
//        moves.setBlackP(BlP);
//
//        uint64_t const empty = ~bitwiseOr(notWP, BlP);
//        moves.setEmpty(empty);
//    }

    this->possibleMoves->setBitboard(this->bitBoards[pieceVal]->useBitboard());

    std::unordered_map<float, std::function<uint64_t()>> map = {
        {1.0f, [moves, this, &squares, index]() {return moves.getPawnMoves(index, this->possibleMoves, squares);}},
        {3.1f, [moves, this, &squares, index]() {return moves.getKnightMoves(index, this->possibleMoves, squares);}},
        {3.2f, [moves, this, &squares, index]() {return moves.getBishopMoves(index, this->possibleMoves, squares);}},
        {5.0f, [moves, this, &squares, index]() {return moves.getRookMoves(index, this->possibleMoves, squares);}},
        {9.0f, [moves, this, &squares, index]() {return moves.getQueenMoves(index, this->possibleMoves, squares);}},
        {0.1f, [moves, this, &squares, index]() {return moves.getKingMoves(index, this->bitBoards, this->possibleMoves, squares);}}
    };

    auto newBoard = map[std::abs(pieceVal)]();

    this->possibleMoves->setBitboard(newBoard);

    for (int i = 0; i < 64; i++) {
        if (((~this->curBitboard->useBitboard() >> i) & 1) == 1) {
            squares[i].setValidMove(false);
        }

        if (((this->possibleMoves->useBitboard() >> i) & 1) == 1) {
            squares[i].changeColor(sf::Color(255, 0, 0));
            squares[i].setValidMove(true);
        }
    }
}

void GameLogic::updateMoves(int const clickedIndex, int const trackedIndex) {
    auto const *squares = this->curBoard->useBoard();

    float const pieceVal = squares[clickedIndex].usePiece();

    // Masks for the Old Square and New Square
    uint64_t const newSpaceMask = 1ULL << clickedIndex;
    uint64_t const oldSpaceMask = bitwiseNot(1ULL << trackedIndex);

    // Sets the new Game State Bitboard
    uint64_t const newBoardMask = bitwiseOr(this->curBitboard->useBitboard(), bitwiseAnd(this->possibleMoves->useBitboard(), newSpaceMask));
    uint64_t const newBoard = bitwiseAnd(newBoardMask, oldSpaceMask);

    this->curBitboard->setBitboard(newBoard);

    std::cout << "New Board: " << newBoard << std::endl;

    // Sets the new Bitboard to the Piece
    uint64_t const newPieceBoardMask = bitwiseOr(this->bitBoards[pieceVal]->useBitboard(), newSpaceMask);
    uint64_t const newPieceBoard = bitwiseAnd(newPieceBoardMask, oldSpaceMask);

    this->bitBoards[pieceVal]->setBitboard(newPieceBoard);

    std::cout << "New PieceVal Board: " << newPieceBoard << std::endl;

    this->revertBitboard();
}

void GameLogic::updateBoard(Board *&board) {
    //this->curBoard = board;
    this->curBoard->setSquares(board->useBoard());
}

void GameLogic::standbyUpdate() {
    this->turnCounter++;
    this->playerTurn = !this->playerTurn;
}

void GameLogic::checkMate() {
    Bitboard *whiteKing = this->bitBoards[0.1f];
    Bitboard *blackKing = this->bitBoards[-0.1f];


}




// Bitwise Operations
uint64_t GameLogic::bitwiseAnd(Bitboard *&board1, Bitboard *&board2) {
    return board1->useBitboard() & board2->useBitboard();
}

uint64_t GameLogic::bitwiseOr(Bitboard *&board1, Bitboard *&board2) {
    return board1->useBitboard() | board2->useBitboard();
}

uint64_t GameLogic::bitwiseNot(Bitboard *&board) {
    return ~board->useBitboard();
}

uint64_t GameLogic::bitwiseAnd(uint64_t const board1, uint64_t const board2) {
    return board1 & board2;
}

uint64_t GameLogic::bitwiseNot(uint64_t const board) {
    return ~board;
}

uint64_t GameLogic::bitwiseOr(uint64_t const board1, uint64_t const board2) {
    return board1 | board2;
}