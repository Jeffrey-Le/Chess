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

bool CustomEvent::squareClickLogic(sf::RenderWindow const &window, Square *clickedSquare, Square *&trackedSquare, int const index) const{
    std::cout << "Square is CLicked" << std::endl;

    if (!clickedSquare->isClicked(window)) {

        uint64_t const diffIndex = trackedSquare - clickedSquare;
        int const temp = index + diffIndex;

        emptySquareClick(clickedSquare, trackedSquare);
        this->logic->updateMoves(index, temp);

        return true;
    }
    else {
        occupiedSquareClick(clickedSquare, trackedSquare);
        this->logic->getPossibleMoves(index);
    }

    return false;

}

void CustomEvent::occupiedSquareClick(Square *&clickedSquare, Square *& trackedSquare) {
    std::cout << "Not Empty" << std::endl;

    clickedSquare->changeColor(sf::Color(0, 0, 175, 150));

    trackedSquare = clickedSquare;

}

void CustomEvent::emptySquareClick(Square *&clickedSquare, Square *& trackedSquare) {
    std::cout << "Empty" << std::endl;

    if (clickedSquare->checkClickable()) {
        clickedSquare->setOccupiedPiece(trackedSquare->useOccupiedPiece());
        clickedSquare->changePiece(trackedSquare->useOccupiedPiece()->useVal());

        trackedSquare->setOccupiedPiece(new Piece());

        //
        // trackedSquare->resetState();
        //
        // clickedSquare->resetState();
    }
}

void  CustomEvent::resetAllSquareStates() {
    // Reset All Square States based on GameLogic Bitboard
}


sf::Event CustomEvent::useCustomEvent() const{
    return this->event;
}


