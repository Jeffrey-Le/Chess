//
// Created by Jeffrey Vo Le on 5/16/24.
//
#include "../include/GameLogic.h"


GameLogic::GameLogic() {
    this->players = new Player[2];

    players[1].setColor("Black");

    this->curBoard = nullptr;
    this->curBitboard = new Bitboard();
    this->possibleMoves = new Bitboard();
    this->validSquares = new Bitboard();

    float values[] = {1.0, 3.1, 3.2, 5.0, 9.0, 0.1};

    for (auto i = 0; i < 6; i++) {
        this->bitBoards[values[i]] = new Bitboard();
        this->bitBoards[-values[i]] = new Bitboard();
    }

}

GameLogic::GameLogic(Board &board) {
    this->players = new Player[2];

    players[1].setColor("Black");

    this->curBoard = &board;
    this->curBitboard = new Bitboard();
    this->possibleMoves = new Bitboard();
    this->validSquares = new Bitboard();

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

            //std::cout << "PieceVal: " << pieceVal << std::endl;

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

    // Sets the new Bitboard to the Piece
    uint64_t const newPieceBoardMask = bitwiseOr(this->bitBoards[pieceVal]->useBitboard(), newSpaceMask);
    uint64_t const newPieceBoard = bitwiseAnd(newPieceBoardMask, oldSpaceMask);

    this->bitBoards[pieceVal]->setBitboard(newPieceBoard);

    // Checks the Future Possible Moves for the Current Piece to See if Move Made King in Check
    this->getPossibleMoves(clickedIndex);

    this->standbyUpdate();

    this->testKingInCheck();

    if (this->kingInCheck) {
        std::unordered_map<char, int> kingPostions = this->findKingPositions();

        King* wKing = dynamic_cast<King*>(squares[kingPostions['w']].useOccupiedPiece()); // Guaranteed to be a King Derived Class
        King* bKing = dynamic_cast<King*>(squares[kingPostions['b']].useOccupiedPiece()); // Guaranteed to be a King Derived Class

        King* kingInCheck = (wKing->isCheck()) ? wKing : bKing;

        this->attackingIndices.push_back(clickedIndex);

        std::vector<uint64_t> allMoves = this->generateMoves(clickedIndex);

        for (auto &move: allMoves) {
            if (move & this->bitBoards[kingInCheck->useVal()]->useBitboard())
                this->attackChecks[move] = true;
            else
                this->attackChecks[move] = false;
        }
    }

    // Intialize new State
    this->revertBitboard();
}

void GameLogic::updateBoard(Board *&board) {
    this->curBoard->setSquares(board->useBoard());

    Square *squares = this->curBoard->useBoard();


    if (!kingInCheck) {
        for (int i = 0; i < 64; i++) {
            if (((this->playerTurn && squares[i].usePiece() > 0.0f) || (!this->playerTurn && squares[i].usePiece() < 0.0f)))
                squares[i].setValidMove(true);
            else
                squares[i].setValidMove(false);
        }
    }
    else {
        for (int i = 0; i < 64; i++) {
            if (((this->playerTurn && squares[i].usePiece() > 0.0f) || (!this->playerTurn && squares[i].usePiece() < 0.0f)) && (this->validSquares->useBitboard() & (1ULL << i))) {
                std::cout << this->validSquares->useBitboard() << std::endl;
                squares[i].setValidMove(true);
            }
            else
                squares[i].setValidMove(false);
        }
    }
}


void GameLogic::standbyUpdate() {
    this->turnCounter++;
    this->playerTurn = !this->playerTurn;
}


void GameLogic::updateValidSquare() {
    Square *squares = this->curBoard->useBoard();

    std::cout << "Setting Board Valid Squares\n\n";

    for (int i = 0; i < 64; i++) {
        if (((this->validSquares->useBitboard() >> i) & 1ULL) == 1ULL) {
            squares[i].setValidMove(true);
        }
    }
}




void GameLogic::testKingInCheck() {
    Square *squares = this->curBoard->useBoard();

    std::unordered_map<char, int> kingPostions = this->findKingPositions();

    int whiteIndex = kingPostions['w'];
    int blackIndex = kingPostions['b'];

    // Check If White King is In Check
    if ((this->possibleMoves->useBitboard() & bitBoards[0.1f]->useBitboard()) != 0ULL) {
        King* king = dynamic_cast<King*>(squares[whiteIndex].useOccupiedPiece()); // Guaranteed to be a King Derived Class

        std::cout << "White King in Check" << std::endl;

        if (king != nullptr) {
            king->setCheck(true);
            this->kingInCheck = true;
        }
    }

    // Check If Black King is In Check
    if ((this->possibleMoves->useBitboard() & bitBoards[-0.1f]->useBitboard()) != 0ULL) {
        King* king = dynamic_cast<King*>(squares[blackIndex].useOccupiedPiece()); // Guaranteed to be a King Derived Class

        std::cout << "Black King in Check" << std::endl;

        if (king != nullptr) {
            king->setCheck(true);
            this->kingInCheck = true;
        }
    }

}


std::unordered_map<char, int> GameLogic::findKingPositions() {
    std::unordered_map<char, int> kingPostions;

    uint64_t whiteKing = this->bitBoards[0.1f]->useBitboard();
    uint64_t blackKing = this->bitBoards[-0.1f]->useBitboard();

    int whiteIndex = 0;
    int blackIndex = 0;

    while (whiteKing != 1ULL) {
        whiteKing >>= 1ULL;
        whiteIndex++;
    }

    while (blackKing != 1ULL) {
        blackKing >>= 1ULL;
        blackIndex++;
    }

    kingPostions['w'] = whiteIndex;
    kingPostions['b'] = blackIndex;

    return kingPostions;
}

King *GameLogic::getPlayerKing() {
    Square const *squares = this->curBoard->useBoard();

    std::unordered_map<char, int> kingPositions = this->findKingPositions();

    King* wKing = dynamic_cast<King*>(squares[kingPositions['w']].useOccupiedPiece()); // Guaranteed to be a King Derived Class
    King* bKing = dynamic_cast<King*>(squares[kingPositions['b']].useOccupiedPiece()); // Guaranteed to be a King Derived Class

    if ((wKing == nullptr) || (bKing == nullptr))
        return nullptr;

    return (this->playerTurn) ? wKing : bKing; // w = true, b = false;
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