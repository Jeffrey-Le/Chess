//
// Created by Jeffrey Vo Le on 5/18/24.
//

#include "../include/CustomEvent.h"

CustomEvent::CustomEvent() {
    std::cout << "Initializing CustomEvent" << std::endl;
}

Piece *CustomEvent::squareClickLogic(sf::RenderWindow &window, Square *squares, Piece *trackedPiece) {
    for (int i = 0; i < 64; i++) {
        if (squares[i].isClicked(window) && squares[i].usePiece() != 0.0f) {
            // Display Blue Squares
            //squares[i].checkPiece();
            std::cout << "Is Clicked is True: " << squares[i].usePiece() << std::endl;
            trackedPiece = squares[i].useOccupiedPiece();
        }

        if (trackedPiece != nullptr && squares[i].usePiece() == 0.0f) {
            std::cout << "Tracked Piece not nullptr INSIDE" << std::endl;
            bool temp = squares[i].checkClickable(window, trackedPiece, trackedPiece->useVal());

            if (temp)
                trackedPiece = nullptr;
        }
    }

    return trackedPiece;
}


sf::Event CustomEvent::useCustomEvent() {
    return this->event;
}


