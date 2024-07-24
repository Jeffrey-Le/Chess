//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Game.h"
#include "../include/CustomEvent.h"
#include "../include/Promotion.h"

Game::Game() {
    this->window.create(sf::VideoMode(960, 720), "SFML Application");

    this->board = new Board(); // Create a new board

    this->interface = new GameInterface();
}

Game::~Game() {
    delete this->board;
    delete this->interface;
}

void Game::openGame() {
    std::cout << "In Open Game \n";

    // Draw Variables
    this->board->drawBoard(); // Setup square board elements

    this->board->startGame();

    //this->board->displayBoard();

    auto *logic = new GameLogic(*this->board, *this->interface);

    Square *squares = this->board->useBoard();

    CustomEvent customEvent(logic);

    for (int i = 0; i < 64; i++) {
        if (squares[i].usePiece() > 0.0f)
            squares[i].setValidMove(true);
        else
            squares[i].setValidMove(false);
    }

    Square *trackedSquare = nullptr;

    bool mate = false;

    while (this->window.isOpen())
    {
        sf::Event event = customEvent.useCustomEvent();

        sf::Vector2i mouseCoords = sf::Mouse::getPosition(this->window);

        this->window.clear(sf::Color(sf::Color(0, 255, 0))); // Clears Canvas

        // Draw Content onto Window
        for (int i = 0; i < 64; i++) {
            this->window.draw(squares[i].useSquare());
            this->window.draw(squares[i].useOccupiedPiece()->useSprite());
        }

        for (int i = 0; i < 8; i++)
        {
            this->window.draw(this->board->usePositions('n')[i]);
            this->window.draw(this->board->usePositions('l')[i]);
        }

        // Draw Interface onto Window
        this->window.draw(this->interface->useTurnUI());
        this->window.draw(this->interface->useColorUI());
        this->window.draw(this->interface->useScoreUI());

//        if (customEvent.usePromotion()) {
//            auto *newPromotion = new Promotion();
//
//            logic->
//
//            newPromotion->drawPromotionUI();
//
//            this->window.draw();
//        }

        this->window.display(); // Display


        // Event to check when user attempts to close window
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();

            if (mate) {
                std::cout << "CHECKMATE GAME OVER" << std::endl;
                this->window.close();
            }

            bool stateEnd = false; // Track the end of a state (Move is Made)

            Promotion *newPromotion = nullptr;

            char color;

            for (int i = 0; i < 64; i++) {
                // Click Logic
                if (event.type == sf::Event::MouseButtonPressed && squares[i].useSquare().getGlobalBounds().contains(mouseCoords.x, mouseCoords.y))
                {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        std::unordered_map<char, int> kingPositions = logic->findKingPositions();

                        King* wKing = dynamic_cast<King*>(squares[kingPositions['w']].useOccupiedPiece()); // Guaranteed to be a King Derived Class
                        King* bKing = dynamic_cast<King*>(squares[kingPositions['b']].useOccupiedPiece()); // Guaranteed to be a King Derived Class

                        std::unordered_map<char, King*> kingPieces = {{'w', wKing}, {'b', bKing}};

                        stateEnd = customEvent.squareClickLogic(kingPieces, &squares[i], trackedSquare, i);

                        color = (squares[i].useOccupiedPiece()->checkWhite()) ? 'w' : 'b';

                        customEvent.setPromotion(color, logic->lookForPromotion(i));
                    }

                    if (event.mouseButton.button == sf::Mouse::Right) {
                        std::cout << "Right Click" << std::endl;

                        squares[i].changeColor(sf::Color(50, 255, 50));
                    }
                }
            }

            // TODO: HUGE BUG; WORK ON MAKING PROMOTION UI APPEAR ON PAWN CLICK
            // PAWN CLICK IS CRASHING WHEN ONE SQUARE AWAY FROM PROMOTION

            if (customEvent.usePromotion()[color])
            {
                newPromotion = new Promotion();

                int const promotionInd = logic->usePromotionSquare();

                newPromotion->drawPromotionUI(squares[promotionInd].useSquare().getPosition());

                this->window.draw(newPromotion->usePromUI());

                this->window.display();
            }

            // THIS INFINITELY LOOPS
//            while (customEvent.usePromotion()[color]) {
//                int const promotionInd = logic->usePromotionSquare();
//
//                if (event.type == sf::Event::MouseButtonPressed && squares[promotionInd].useSquare().getGlobalBounds().contains(mouseCoords.x, mouseCoords.y)) {
//                    if (event.mouseButton.button == sf::Mouse::Left) {
//                        customEvent.promotionClick(&squares[promotionInd]);
//                        std::cout << "Setting to false\n";
//                    }
//                    else
//                        std::cout << "Still True\n";
//                }
//            }

            if (stateEnd && !customEvent.usePromotion()[color]) {
                // Reset State
                for (int i = 0; i < 64; i++) {
                    squares[i].resetState();
                }

                this->board->setSquares(squares); // Update Board

                std::cout << "Updating Board" << std::endl;

                logic->standbyUpdate();

                logic->getPossibleMovesInCheck(); // Looks for Check

                logic->updateBoard(this->board); // Update Logic

                mate = logic->lookForCheckmate();

                // Update Interface
                this->interface->setScoreUI();
                this->interface->setTurnCounter(this->interface->useTurnCounter() + 1);
                this->interface->inverseWhite();
            }
        }
    }

}

