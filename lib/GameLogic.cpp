//
// Created by Jeffrey Vo Le on 5/16/24.
//
#include "../include/GameLogic.h"

#include <memory>


GameLogic::GameLogic() {
    this->players = new Player[2];

    this->curBoard = nullptr;
    this->curBitboard = new Bitboard();

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
        std::string key = std::to_string(std::tolower(name) + 'w');

        float const pieceVal = PieceInfo[key];

        this->bitBoards[pieceVal]->displayBitboard();
    }

    if (color == 'w') {
        std::string key = std::to_string(std::tolower(name) + 'b');

        float const pieceVal = PieceInfo[key];

        this->bitBoards[pieceVal]->displayBitboard();
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
            this->possibleMoves = this->whitePawn;

            moves.getPawnMoves(1, this->possibleMoves,squares, index);
            //
            // uint64_t const temp = ~(1ULL << index);
            //
            // bitwiseOr(this->curBitboard->useBitboard(), temp);
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

void GameLogic::updateMoves(int const clickedIndex, int const trackedIndex) {
    auto const *squares = this->curBoard->useBoard();

    uint64_t const newBoard = this->curBitboard->useBitboard() | bitwiseAnd(this->possibleMoves->useBitboard(), (1ULL << clickedIndex)) & ~(1ULL << trackedIndex);

    std::cout << "New Board: " << newBoard << std::endl;

    for (int i = 0; i < 64; i++) {
        if (((newBoard >> i) & 1) == 1) {
            squares[i].changeColor(sf::Color(50, 255, 50));
        }
    }


}

void GameLogic::updateBoard(Board *&board) const {
    this->curBoard->setSquares(board->useBoard());
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