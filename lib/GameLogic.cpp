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
    this->interface = nullptr;

    float values[] = {1.0, 3.1, 3.2, 5.0, 9.0, 0.1};

    for (auto i = 0; i < 6; i++) {
        this->bitBoards[values[i]] = new Bitboard();
        this->bitBoards[-values[i]] = new Bitboard();
    }

}

GameLogic::GameLogic(Board &board, GameInterface &interface) {
    this->players = new Player[2];

    players[1].setColor("Black");

    this->curBoard = &board;
    this->curBitboard = new Bitboard();
    this->possibleMoves = new Bitboard();
    this->validSquares = new Bitboard();
    this->interface = &interface;

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
    auto *squares = this->curBoard->useBoard();

    if (this->enPeasant) {
        Bitboard *opposingPawn = (this->playerTurn) ? this->bitBoards[-1.0f] : this->bitBoards[1.0f];

        int capIndex = -1;

        if ((1ULL << (clickedIndex + 8)) & opposingPawn->useBitboard() && this->playerTurn)
            capIndex = clickedIndex + 8;
        else if ((1ULL << (clickedIndex - 8)) & opposingPawn->useBitboard() && !this->playerTurn)
            capIndex = clickedIndex - 8;

        if (capIndex != -1) {
            this->capturePiece(capIndex);

            squares[capIndex].setOccupiedPiece(new Piece());
        }

        this->enPeasant = false;
        this->enPeasontPos = -1;
    }

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

    // Check En Pesant
    this->lookForEnPeasant(clickedIndex, trackedIndex);

    if (this->enPeasant)
        this->enPeasontPos = clickedIndex;
    else
        this->enPeasontPos = -1;

    // Check if on Promotion Square
    this->moves.checkPawnPromotion(squares, clickedIndex);

    // Checks the Future Possible Moves for the Current Piece to See if Move Made King in Check
    this->getPossibleMoves(clickedIndex);

    this->testKingInCheck();

    if (this->kingInCheck) {
        std::unordered_map<char, int> kingPostions = this->findKingPositions();

        King* wKing = dynamic_cast<King*>(squares[kingPostions['w']].useOccupiedPiece()); // Guaranteed to be a King Derived Class
        King* bKing = dynamic_cast<King*>(squares[kingPostions['b']].useOccupiedPiece()); // Guaranteed to be a King Derived Class

        King* kingInCheck = (wKing->isCheck()) ? wKing : bKing;

        this->attackingIndices.push_back(clickedIndex);

        std::vector<uint64_t> allMoves = this->generateMoves(clickedIndex);

        // for (auto &move: allMoves)
        //     std::cout << "AttackMove: " << move << std::endl;

        for (auto &move: allMoves) {
            move &= ~(1ULL << clickedIndex);
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
    //this->validSquares->setBitboard(0ULL);

    Square *squares = this->curBoard->useBoard();

    if (!kingInCheck) {
        for (int i = 0; i < 64; i++) {
            if (((this->playerTurn && squares[i].usePiece() > 0.0f) || (!this->playerTurn && squares[i].usePiece() < 0.0f)))
                //squares[i].setValidMove(true);
                this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
            else
                squares[i].setValidMove(false);
        }
    }
    else {
        for (int i = 0; i < 64; i++) {
            if (((this->playerTurn && squares[i].usePiece() > 0.0f) || (!this->playerTurn && squares[i].usePiece() < 0.0f)) && (this->validSquares->useBitboard() & (1ULL << i))) {
                this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
                //squares[i].setValidMove(true);
            }
            else
                squares[i].setValidMove(false);
        }
    }

    this->updateValidSquare();
}


void GameLogic::standbyUpdate() {
    this->turnCounter++;
    this->playerTurn = !this->playerTurn;
}


void GameLogic::updateValidSquare() {
    Square *squares = this->curBoard->useBoard();

    std::cout << "Setting Board Valid Squares\n\n";

    char color = (this->playerTurn) ? 'w' : 'b';

    for (int i = 0; i < 64; i++) {
        if (((this->validSquares->useBitboard() >> i) & 1ULL) == 1ULL) {
            squares[i].setValidMove(true);
        }
        else if ((squares[i].usePiece() > 0.0f && color == 'b') || (squares[i].usePiece() < 0.0f && color == 'w'))
            squares[i].setValidMove(false);
    }

    //std::cout << "New Valid Squares: " << this->validSquares->useBitboard() << std::endl;;
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


bool GameLogic::lookForCheckmate() {
    Square *squares = this->curBoard->useBoard();
    std::unordered_map<char, int> kingPos = this->findKingPositions();
    King *king = getPlayerKing();

    char const color = (king->checkWhite()) ? 'w' : 'b';

    if (this->kingInCheck && king->isCheck()) {

        // Generate Moves for all pieces
        std::vector<uint64_t> allMoves = this->generateMoves(kingPos[color]);

        uint64_t comboMoves = 0ULL;

        for (auto &move: allMoves)
            comboMoves |= move;

        std::cout << this->validSquares->useBitboard() << std::endl;

        if (comboMoves == 0ULL && (this->validSquares->useBitboard() == (1ULL << kingPos[color])))
            return true;
    }

    return false;
}

void GameLogic::lookForEnPeasant(int clickedIndex, int trackedIndex) {
    // CHeck to see that the opposing pawn has made a 2 move forwards
    if (((clickedIndex - 16) != trackedIndex && !this->playerTurn) || ((clickedIndex + 16) != trackedIndex && this->playerTurn))
        return;

    int left = clickedIndex - 1;
    int right = clickedIndex + 1;

    Bitboard *opposingPawn = (this->playerTurn) ? this->bitBoards[-1.0f] : this->bitBoards[1.0f];

    if ((((1ULL << left) & opposingPawn->useBitboard()) != 0ULL) || (((1ULL << right) & opposingPawn->useBitboard()) != 0ULL))
        this->enPeasant = true;
}

bool GameLogic::lookForPromotion(int const clickedIndex) {
    auto const squares = this->curBoard->useBoard();

    auto pawn = dynamic_cast<Pawn*>(squares[clickedIndex].useOccupiedPiece());

    if (pawn != nullptr && pawn->checkPromotion()) {
        return true;
    }

    return false;
}



bool GameLogic::usePlayerTurn() const {
    return this->playerTurn;
}

int GameLogic::usePromotionSquare() const {
    return this->moves.usePromotionInd(this->curBoard->useBoard());
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