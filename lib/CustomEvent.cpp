//
// Created by Jeffrey Vo Le on 5/18/24.
//

#include "../include/CustomEvent.h"

CustomEvent::CustomEvent() {
    std::cout << "Initializing CustomEvent" << std::endl;
}

CustomEvent::CustomEvent(GameLogic *&existingLogic) {
    std::cout << "Initializing CustomEvent" << std::endl;

    this->logic = existingLogic;
}

bool CustomEvent::squareClickLogic(std::unordered_map<char, King*> kingPieces, Square *clickedSquare, Square *&trackedSquare, int const index) const{
    //std::cout << "Square is CLicked" << std::endl;

    King* kingInCheck = kingPieces['w']->isCheck() ? kingPieces['w'] : kingPieces['b'];

    if (clickedSquare->checkValid()) {
        if (clickedSquare->checkEmpty() && trackedSquare != nullptr) {
            int const sum = (clickedSquare->kingSide() && clickedSquare->useCastle()) ? 1 : -2;

            auto rookNewSquare = (clickedSquare->kingSide() && clickedSquare->useCastle()) ? (clickedSquare - 1) : (clickedSquare + 1);
            auto rookOldSquare = clickedSquare + sum;

            Rook* rook = (clickedSquare->useCastle()) ? dynamic_cast<Rook*>(rookOldSquare->useOccupiedPiece()) : nullptr;
            King* king = (clickedSquare->useCastle()) ? dynamic_cast<King*>(trackedSquare->useOccupiedPiece()) : nullptr;

            int const diffIndex = trackedSquare - clickedSquare;
            int const temp = index + diffIndex;

            if (rook != nullptr && rook->checkFirstMove() && clickedSquare->useCastle())
            {
                int rookIndex; // find index

                if (rook->checkWhite()) {
                    if (clickedSquare->kingSide())
                        rookIndex = 61;
                    else
                        rookIndex = 59;
                }
                else {
                    if (clickedSquare->kingSide())
                        rookIndex = 5;
                    else
                        rookIndex = 3;
                }

                int const rookDiffIndex = rookOldSquare - rookNewSquare;
                int const rookTemp = rookIndex + rookDiffIndex;

                rook->setFirstMove();
                swapSquareClick(rookNewSquare, rookOldSquare);

                this->logic->updateMoves(rookIndex, rookTemp);
            }

            std::cout << "Before SwapSquareClick: " << clickedSquare << "\n" << trackedSquare << "\n";

            swapSquareClick(clickedSquare, trackedSquare);

            std::cout << "After SwapSquareClick\n";

            if (kingInCheck != nullptr && kingInCheck->isCheck())
                kingInCheck->setCheck(false);

            if (king != nullptr && king->checkFirstMove())
                king->setFirstMove();

            this->logic->updateMoves(index, temp);

            return true;
        }
        else {
            if (trackedSquare != clickedSquare && trackedSquare != nullptr) {
                trackedSquare->resetState();
                this->logic->resetPossibleMoves();
            }

            if ((this->logic->usePlayerTurn() && clickedSquare->usePiece() > 0.0f) || (!this->logic->usePlayerTurn() && clickedSquare->usePiece() < 0.0f)) {
                occupiedSquareClick(clickedSquare, trackedSquare);
                this->logic->getPossibleMoves(index);
            }
            else if (trackedSquare != nullptr) {
                int const diffIndex = trackedSquare - clickedSquare;
                int const temp = index + diffIndex;

                this->logic->capturePiece(index);
                swapSquareClick(clickedSquare, trackedSquare);

                if (kingInCheck != nullptr && kingInCheck->isCheck())
                    kingInCheck->setCheck(false);

                this->logic->updateMoves(index, temp);
                return true;
            }
        }
    }
    else
        std::cout << "Not Correct Color" << std::endl;

    return false;

}

void CustomEvent::occupiedSquareClick(Square *&clickedSquare, Square *& trackedSquare) {
    //std::cout << "Not Empty" << std::endl;

    clickedSquare->changeColor(sf::Color(0, 0, 175, 150));

    trackedSquare = clickedSquare;


}

void CustomEvent::swapSquareClick(Square *&clickedSquare, Square *& trackedSquare) {
    //std::cout << "Empty" << std::endl;

    Pawn* pawn = dynamic_cast<Pawn*>(trackedSquare->useOccupiedPiece());

    if (pawn != nullptr)
        pawn->setFirstMove();

    clickedSquare->setValidMove(true);
    clickedSquare->setOccupiedPiece(trackedSquare->useOccupiedPiece());

    trackedSquare->setOccupiedPiece(new Piece());
}

void CustomEvent::promotionClick(Square *square) {
    char color = (square->useOccupiedPiece()->checkWhite()) ? 'w' : 'b';

    this->isPromoted[color] = false;
}

void CustomEvent::setPromotion(char const color, bool const val) {
    this->isPromoted[color] = val;
}


sf::Event CustomEvent::useCustomEvent() const{
    return this->event;
}

std::unordered_map<char, bool> CustomEvent::usePromotion() const {
    return this->isPromoted;
}


