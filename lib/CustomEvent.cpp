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
            int const diffIndex = trackedSquare - clickedSquare;
            int const temp = index + diffIndex;

            emptySquareClick(clickedSquare, trackedSquare);

            if (kingInCheck != nullptr && kingInCheck->isCheck())
                kingInCheck->setCheck(false);

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
                //this->captureSquareClick(clickedSquare, trackedSquare);
                emptySquareClick(clickedSquare, trackedSquare);

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

void CustomEvent::emptySquareClick(Square *&clickedSquare, Square *& trackedSquare) {
    //std::cout << "Empty" << std::endl;

    Pawn* pawn = dynamic_cast<Pawn*>(trackedSquare->useOccupiedPiece());

    if (pawn != nullptr)
        pawn->setFirstMove();

    clickedSquare->setValidMove(true);
    clickedSquare->setOccupiedPiece(trackedSquare->useOccupiedPiece());

    trackedSquare->setOccupiedPiece(new Piece());
}

void CustomEvent::captureSquareClick(Square *&clickedSquare, Square *&trackedSquare) {
    //std::cout << "In Capture Square Click" << std::endl;

    //clickedSquare->setValidMove(false);
    clickedSquare->setOccupiedPiece(trackedSquare->useOccupiedPiece());

    trackedSquare->setOccupiedPiece(new Piece());
}



sf::Event CustomEvent::useCustomEvent() const{
    return this->event;
}


