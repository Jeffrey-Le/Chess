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

    int multiplier =  (playerTurn) ? 1 : -1; // w = 1, b = -1

    uint64_t notPlayerP = this->bitBoards[pieceVal]->useBitboard();

    for (auto &bitBoard: this->bitBoards) {
        if ((multiplier > 0 && bitBoard.first > 0.0f) || (multiplier < 0 && bitBoard.first < 0.0f))
            notPlayerP = bitwiseOr(notPlayerP, bitBoard.second->useBitboard());
    }

    //notPlayerP = bitwiseOr(notPlayerP, this->bitBoards[-0.1f * float(multiplier)]->useBitboard());

    this->moves.setPlayerP(notPlayerP);

    //std::cout << "PlayerP: " << notPlayerP << std::endl;

    uint64_t opposingP = this->bitBoards[-1.0f * float(multiplier)]->useBitboard();

    for (auto &bitBoard : this->bitBoards) {
        //if (bitBoard.first == (-1.0f * float(multiplier)) || bitBoard.first == (-0.1f * float(multiplier)))
        if (bitBoard.first == (-1.0f * float(multiplier)))
            continue;

        if ((multiplier > 0 && bitBoard.first < 0.0f) || (multiplier < 0 && bitBoard.first > 0.0f)) {
            opposingP = bitwiseOr(opposingP, bitBoard.second->useBitboard());
        }
    }

    //std::cout << "Opposing: " << opposingP << std::endl;

    this->moves.setOpposingP(opposingP);

    uint64_t const empty = ~bitwiseOr(notPlayerP, opposingP);
    moves.setEmpty(empty);

    this->possibleMoves->setBitboard(this->bitBoards[pieceVal]->useBitboard());

    std::unordered_map<float, std::function<std::vector<uint64_t>()>> map = {
        {1.0f, [this, &squares, index]() {
            return this->moves.getPawnMoves(index, this->possibleMoves, squares);
        }},
        {3.1f, [this, &squares, index]() {
            return this->moves.getKnightMoves(index, this->possibleMoves, squares);
        }},
        {3.2f, [this, &squares, index]() {
            return this->moves.getBishopMoves(index, this->possibleMoves, squares);
        }},
        {5.0f, [this, &squares, index]() {
            return this->moves.getRookMoves(index, this->possibleMoves, squares);

        }},
        {9.0f, [this, &squares, index]() {
           return this->moves.getQueenMoves(index, this->possibleMoves, squares);

        }},
        {0.1f, [this, &squares, index]() {
            return this->moves.getKingMoves(index, this->bitBoards, this->possibleMoves, squares);
        }}
    };

    auto newBoard = map[std::abs(pieceVal)]();

    // for (auto &move: newBoard) {
    //     if (move & bitBoards[-0.1f * multiplier] != 0ULL)
    //         this->attackChecks[move] = true;
    //     else
    //         this->attackChecks[move] = false;
    // }

    return newBoard;
}


void GameLogic::getPossibleMoves(int const index) {
    this->validSquares->setBitboard(0ULL);

    float mult = (playerTurn) ? 1 : -1;

    Square *squares = this->curBoard->useBoard();

    std::vector<uint64_t> allMoves = this->generateMoves(index);

    if (squares[index].usePiece() == (1.0f * mult))
        allMoves[1] = (allMoves[1] & moves.useOpposingP());

    uint64_t combMoves = 0ULL;

    for (auto &move: allMoves) {
        combMoves |= move;
    }

    this->possibleMoves->setBitboard(combMoves);

    std::cout << "PossibleMoves: " << this->possibleMoves->useBitboard() << std::endl;

    for (int i = 0; i < 64; i++) {
        if (((~this->curBitboard->useBitboard() >> i) & 1) == 1) {
            //squares[i].setValidMove(false);
            this->validSquares->setBitboard(this->validSquares->useBitboard() & ~(1ULL << i));
        }

        if (((this->possibleMoves->useBitboard() >> i) & 1) == 1) {
            squares[i].changeColor(sf::Color(255, 0, 0));
            //squares[i].setValidMove(true);
            this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << i));
        }
    }

    this->updateValidSquare();

}

// --------------------------------------------------

void GameLogic::getPossibleCheckedMoves() {
    this->validSquares->setBitboard(0ULL);

    Square *squares = this->curBoard->useBoard();

    std::unordered_map<char, int> kingPositions = this->findKingPositions();

    King* wKing = dynamic_cast<King*>(squares[kingPositions['w']].useOccupiedPiece()); // Guaranteed to be a King Derived Class
    King* bKing = dynamic_cast<King*>(squares[kingPositions['b']].useOccupiedPiece()); // Guaranteed to be a King Derived Class

   if ((wKing == nullptr) || (bKing == nullptr))
       return;

    if ((!wKing->isCheck()) && (!bKing->isCheck()) || (this->attackingIndices.empty())) {
        std::cout << "NO KINGS IN CHECK" << std::endl;
        this->kingInCheck = false;
        return;
    }

    int kingInCheckInd = (wKing->isCheck()) ? kingPositions['w'] : kingPositions['b'];

    // Get the possible Moves for the attackingPiece
    this->playerTurn = !this->playerTurn;
    this->getPossibleMoves(attackingIndices[0]);
    this->playerTurn = !this->playerTurn;

    this->validSquares->setBitboard(0ULL);


    uint64_t const attackingMoves = this->possibleMoves->useBitboard();
    auto knight = dynamic_cast<Knight*>(squares[attackingIndices[0]].useOccupiedPiece()); // Check if Piece is Knight
    auto pawn = dynamic_cast<Pawn*>(squares[attackingIndices[0]].useOccupiedPiece()); // Check if Piece is Pawn


    std::cout << std::endl << "In Possible Checked Moves" << std::endl << std::endl;

    std::cout << std::endl << "AttackingIndex: " << attackingIndices[0] << std::endl;


    for (auto &board: this->bitBoards) {
        if ((board.first > 0.0f)) {
            uint64_t pieceBoard = board.second->useBitboard();

            uint64_t valid = this->validSquares->useBitboard();

            // Loops Over Every Bit
            for (int i = 0; i < 64; i++) {
                if (pieceBoard == 1ULL)
                    break;

                if ((pieceBoard & 1ULL) == 1ULL) { // Means It Found a Peice

                    uint64_t curPieceMove = 0ULL;

                    auto pawnP = dynamic_cast<Pawn*>(squares[i].useOccupiedPiece()); // Check if Piece is Pawn

                    // if (pawnP != nullptr)
                    //     curPieceMove = this->generateMoves(i)[1];
                    // else {
                    std::vector<uint64_t> allMoves = this->generateMoves(i);

                    for (auto &move: allMoves) {
                        curPieceMove |= move;
                    }
                    //}

                    this->possibleMoves->setBitboard(curPieceMove);

                    std::cout << "Checking Pieceboard Checks" << std::endl;

                    // If Attacking Piece is a Sliding Piece
                    // Check if Any Pieces can Capture

                    bool cond1 = (pawnP == nullptr) && (this->possibleMoves->useBitboard() & (1ULL << attackingIndices[0]));
                    bool cond2 = (pawnP != nullptr) && (allMoves[1] & (1ULL << attackingIndices[0]));

                    if ((cond1 || cond2) && (knight == nullptr) && (pawn == nullptr))
                        this->validSquares->setBitboard(valid | (1ULL << i));
                    else
                        this->validSquares->setBitboard(valid & ~(1ULL << i));

                    // Sliding Pieces
                    // Check if Any Pieces can Block
                    for (auto &move: this->attackChecks) {
                        if (move.second && (move.first & this->possibleMoves->useBitboard()) && (knight == nullptr) && (pawn == nullptr)) {
                            this->validSquares->setBitboard(valid | (1ULL << i));
                        }
                    }


                    // If Attacking Piece is a Knight
                    // Must Capture
                    if ((cond1 || cond2) && (knight != nullptr))
                        this->validSquares->setBitboard(valid | (1ULL << i));
                    else
                        this->validSquares->setBitboard(valid & ~(1ULL << i));

                    // If Attacking Piece is a Pawn
                    // Must Capture
                    if ((this->possibleMoves->useBitboard() & (1ULL << attackingIndices[0])) && (pawn != nullptr))
                        this->validSquares->setBitboard(valid | (1ULL << i));
                    else
                        this->validSquares->setBitboard(valid & ~(1ULL << i));

                }
                pieceBoard >>= 1;
            }
        }
    }

    std::cout << "AFter Loop" << std::endl;
    this->validSquares->setBitboard(this->validSquares->useBitboard() | (1ULL << kingInCheckInd));

    this->updateValidSquare();
}
