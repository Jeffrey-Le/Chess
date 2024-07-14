//
// Created by Crolw on 6/22/2024.
//

#include "../include/GameLogic.h"


void GameLogic::resetPossibleMoves() {
    Square *squares = this->curBoard->useBoard();

    for (int i = 0; i < 64; i++) {
        if (((this->possibleMoves->useBitboard() >> i) & 1) == 1) {
            squares[i].resetState();
        }
    }
}

std::vector<uint64_t> GameLogic::generateMoves(int const index) {
    Square *squares = this->curBoard->useBoard();

    float const pieceVal = squares[index].usePiece();

    float multiplier =  (playerTurn) ? 1 : -1; // w = 1, b = -1

    // Sets the Player Pieces
    uint64_t playerP = this->bitBoards[pieceVal]->useBitboard();

    for (auto &bitBoard: this->bitBoards) {
        if ((multiplier > 0 && bitBoard.first > 0.0f) || (multiplier < 0 && bitBoard.first < 0.0f))
            playerP = bitwiseOr(playerP, bitBoard.second->useBitboard());
    }

    //notPlayerP = bitwiseOr(notPlayerP, this->bitBoards[-0.1f * float(multiplier)]->useBitboard());

    this->moves.setPlayerP(playerP);

    //std::cout << "PlayerP: " << notPlayerP << std::endl;

    // Sets the other color Pieces
    uint64_t opposingP = this->bitBoards[-1.0f * multiplier]->useBitboard();

    for (auto &bitBoard : this->bitBoards) {
        //if (bitBoard.first == (-1.0f * float(multiplier)) || bitBoard.first == (-0.1f * float(multiplier)))
        if (bitBoard.first == (-1.0f * multiplier))
            continue;

        if ((multiplier > 0 && bitBoard.first < 0.0f) || (multiplier < 0 && bitBoard.first > 0.0f))
            opposingP = bitwiseOr(opposingP, bitBoard.second->useBitboard());
    }

    //std::cout << "Opposing: " << opposingP << std::endl;

    this->moves.setOpposingP(opposingP);

    // Sets Empty Pieces
    uint64_t const empty = ~bitwiseOr(playerP, opposingP);
    this->moves.setEmpty(empty);

    this->possibleMoves->setBitboard(this->bitBoards[pieceVal]->useBitboard()); // Set starting Bitboard

    std::unordered_map<float, std::function<std::vector<uint64_t>()>> map = {
        {1.0f, [this, &squares, index]() {return this->moves.getPawnMoves(index, this->possibleMoves, squares, this->enPeasontPos);}},
        {3.1f, [this, &squares, index]() {return this->moves.getKnightMoves(index, this->possibleMoves, squares);}},
        {3.2f, [this, &squares, index]() {return this->moves.getBishopMoves(index, this->possibleMoves, squares);}},
        {5.0f, [this, &squares, index]() {return this->moves.getRookMoves(index, this->possibleMoves, squares);}},
        {9.0f, [this, &squares, index]() {return this->moves.getQueenMoves(index, this->possibleMoves, squares);}},
        {0.1f, [this, &squares, index]() {return this->moves.getKingMoves(index, this->bitBoards, this->possibleMoves, squares);}}
    };

    return map[std::abs(pieceVal)]();
}


void GameLogic::getPossibleMoves(int const index) {
    this->validSquares->setBitboard(0ULL);

    float multiplier = (this->playerTurn) ? 1.0f : -1.0f;

    Square *squares = this->curBoard->useBoard();

    std::vector<uint64_t> allMoves = this->generateMoves(index);

    if (squares[index].usePiece() == (1.0f * multiplier)) // Only Applies to Pawns
        allMoves[1] = (allMoves[1] & moves.useOpposingP());

    uint64_t comboMoves = 0ULL;
    uint64_t movesInCheck = 0ULL;

    // Recurring loop that combines all possible moves
    for (auto &move: allMoves)
        comboMoves |= move;

    for (auto &move: this->playerMovesInCheck)
        movesInCheck |= move;

    if (this->kingInCheck && squares[index].usePiece() == (0.1f * multiplier) && ((comboMoves & (1ULL << attackingIndices[0])) != 0ULL)) // If King is in Check but not in range to capture
        movesInCheck &= ~(1ULL << attackingIndices[0]);

    if (this->kingInCheck && squares[index].usePiece() != (0.1f * multiplier)) // If Player is In Check => Ensures the Possilbe Moves are valid for the Piece
        this->possibleMoves->setBitboard(comboMoves & movesInCheck);
    else
        this->possibleMoves->setBitboard(comboMoves & ~movesInCheck); // Normal Moves

    //std::cout << "PossibleMoves: " << this->possibleMoves->useBitboard() << std::endl;

    for (int i = 0; i < 64; i++) {
        // Sets all empty square bits to 0
        if (((~this->curBitboard->useBitboard() >> i) & 1) == 1) {
            //this->validSquares->setBitboard(this->validSquares->useBitboard() & ~(1ULL << i));
            squares[i].setValidMove(false);
        }

        // Changes the color of bits that are possible moves and sets bits to 1
        if (((this->possibleMoves->useBitboard() >> i) & 1) == 1) {
            squares[i].changeColor(sf::Color(255, 0, 0));
            this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
        }
    }

    this->updateValidSquare();
}

// --------------------------------------------------

void GameLogic::getPossibleMovesInCheck() {
    this->validSquares->setBitboard(0ULL);
    this->playerMovesInCheck.clear();

    float mult = (playerTurn) ? 1 : -1;

    Square *squares = this->curBoard->useBoard();

    std::unordered_map<char, int> kingPositions = this->findKingPositions();

    King* wKing = dynamic_cast<King*>(squares[kingPositions['w']].useOccupiedPiece()); // Guaranteed to be a King Derived Class
    King* bKing = dynamic_cast<King*>(squares[kingPositions['b']].useOccupiedPiece()); // Guaranteed to be a King Derived Class

   if ((wKing == nullptr) || (bKing == nullptr)) // If Kings Exist => Should Always unless bug occurs
       return;

    if ((!wKing->isCheck()) && (!bKing->isCheck()) || (this->attackingIndices.empty())) { // Base Case
        this->kingInCheck = false;
        this->attackingIndices.clear();
        this->attackChecks.clear();
        this->playerMovesInCheck.clear();
        return;
    }

    int kingInCheckInd = (wKing->isCheck()) ? kingPositions['w'] : kingPositions['b'];

    auto atkKnight = dynamic_cast<Knight*>(squares[attackingIndices[0]].useOccupiedPiece()); // Check if Piece is Knight
    auto atkPawn = dynamic_cast<Pawn*>(squares[attackingIndices[0]].useOccupiedPiece()); // Check if Piece is Pawn

    // Loop Each Piece Bitboard
    for (auto &board: this->bitBoards) {
        if ((board.first > (0.1f * mult)) || (board.first < (0.1f * mult))) {
            uint64_t pieceBoard = board.second->useBitboard();

            // Loops Over Every Bit
            for (int i = 0; i < 64; i++) {
                if ((pieceBoard & 1ULL) == 1ULL) { // Means It Found a Peice
                    uint64_t valid = this->validSquares->useBitboard();

                    uint64_t curPieceMove = 0ULL;

                    auto pawnP = dynamic_cast<Pawn*>(squares[i].useOccupiedPiece()); // Check if PlayerP is a Pawn

                    std::vector<uint64_t> allMoves = this->generateMoves(i);

                    for (auto &move: allMoves) {
                        curPieceMove |= move;
                    }

                    this->possibleMoves->setBitboard(curPieceMove);

                    bool generalCond = (pawnP == nullptr) && (this->possibleMoves->useBitboard() & (1ULL << attackingIndices[0])); // Checks every other PlayerP if it can capture piece
                    bool pawnCond = (pawnP != nullptr) && (allMoves[1] & (1ULL << attackingIndices[0])); // Checks if PlayerP is a pawn and if it can capture piece

                    // If Attacking Piece is a Sliding Piece
                    // Check if Any Pieces can Capture
                    if ((generalCond || pawnCond) && (atkKnight == nullptr) && (atkPawn == nullptr)) {
                        this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
                        this->playerMovesInCheck.insert((1ULL << attackingIndices[0]));
                    }
                    else
                        this->validSquares->setBitboard(valid & ~(1ULL << i));

                    // Sliding Pieces
                    // Check if Any Pieces can Block
                    // attackChecks<BitBoard, inCheck?>
                    for (auto &move: this->attackChecks) {
                        std::cout << move.second << std::endl;
                        if (move.second && (pawnP == nullptr) && (move.first & this->possibleMoves->useBitboard()) && (atkKnight == nullptr) && (atkPawn == nullptr)) {
                            this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
                            this->playerMovesInCheck.insert(this->possibleMoves->useBitboard() & move.first);
                        }
                        else if (move.second && (pawnP != nullptr) && (move.first & allMoves[0]) && (atkKnight == nullptr) && (atkPawn == nullptr)) {
                            this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
                            this->playerMovesInCheck.insert(allMoves[0] & move.first);
                        }
                    }

                    // If Attacking Piece is a Knight or Pawn
                    // Must Capture
                    if ((generalCond || pawnCond) && ((atkKnight != nullptr) || (atkPawn != nullptr))) {
                        this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
                        this->playerMovesInCheck.insert((1ULL << attackingIndices[0]));
                    }
                    else if ((atkKnight != nullptr) || (atkPawn != nullptr))
                        this->validSquares->setBitboard(this->validSquares->useBitboard() & ~(1ULL << i));
                }
                pieceBoard >>= 1; // Move one bit
            }
        }
    }

    this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << kingInCheckInd)); // Allows King to Move

    this->validSquares->setBitboard(this->validSquares->useBitboard() & ~(1ULL << attackingIndices[0]));

    this->updateValidSquare();
}

void GameLogic::capturePiece(int const index) {
    Square *squares = this->curBoard->useBoard();

    std::cout << "Index: " << index << std::endl;

    uint64_t const BITBOARD = ~(1ULL << index);

    this->bitBoards[squares[index].usePiece()]->setBitboard(this->bitBoards[squares[index].usePiece()]->useBitboard() & BITBOARD);

    this->interface->incrementScore(squares[index].usePiece());
}

