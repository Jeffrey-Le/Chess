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

void CustomEvent::squareClickLogic(sf::RenderWindow const &window, Square *& squares, Square *&trackedPiece, sf::Event &event) const{
    bool temp = false;

    for (int i = 0; i < 64; i++) {
        if (squares[i].isClicked(window) && squares[i].usePiece() != 0.0f) {
            // Display Blue Squares
            //squares[i].checkPiece();
            trackedPiece = &squares[i];
            std::cout << "Is Clicked is True: " << squares[i].usePiece() << std::endl;
            trackedPiece->setOccupiedPiece(squares[i].useOccupiedPiece());

            std::cout << "Tracked Piece: " << trackedPiece->usePiece() << std::endl;
            std::cout << "Occupied Piece: " << &squares[i] << std::endl;

            this->logic->getPossibleMoves(i);
        }

        if (trackedPiece != nullptr && squares[i].usePiece() == 0.0f) {
            std::cout << "Tracked Piece not nullptr INSIDE" << std::endl;
            temp = squares[i].checkClickable(window, trackedPiece->useOccupiedPiece(), trackedPiece->useOccupiedPiece()->useVal());

            std::cout << "Temp: " << temp << std::endl;

            std::cout << "Tracked Piece SEt: " << trackedPiece << std::endl;

            if (temp) {
                auto  *tempPiece = new Piece();
                tempPiece->setValue(0.0f);
                trackedPiece->setOccupiedPiece(tempPiece);
                trackedPiece = nullptr;

                std::cout << "Turinging Tracked Piece to NullPtr: " << trackedPiece << std::endl;
                delete tempPiece;
            }
        }

        squares[i].resetState();
    }


}


sf::Event CustomEvent::useCustomEvent() const{
    return this->event;
}


