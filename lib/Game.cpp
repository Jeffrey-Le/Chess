//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Game.h"
#include "../include/CustomEvent.h"

Game::Game() {
    this->window.create(sf::VideoMode(960, 720), "SFML Application");

    this->board = new Board(); // Create a new board

    this->myMouse = new sf::Mouse();

    this->interface = new GameInterface();
}

Game::~Game() {
    delete this->board;
    delete this->interface;
    delete this->myMouse;
}

void Game::openGame() {
    std::cout << "In Open Game \n";

    // Draw Variables
    this->board->drawBoard(); // Setup square board elements

    this->board->startGame();

    //this->board->displayBoard();

    auto *logic = new GameLogic(*this->board);

    Square *squares = this->board->useBoard();

    Square *track = nullptr;

    CustomEvent customEvent(logic);

    for (int i = 0; i < 64; i++) {
        if (squares[i].usePiece() > 0.0f)
            squares[i].setValidMove(true);
        else
            squares[i].setValidMove(false);
    }

    while (this->window.isOpen())
    {
        logic->checkMate();

        sf::Event event = customEvent.useCustomEvent();
        //sf::Event event; // CustomEvent

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

        this->window.draw(this->interface->useTurnUI());
        this->window.draw(this->interface->useColorUI());

        this->window.display(); // Display


        // Event to check when user attempts to close window
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();

            bool temp = false;

            for (int i = 0; i < 64; i++) {
                // Click Logic
                if (event.type == sf::Event::MouseButtonPressed && squares[i].useSquare().getGlobalBounds().contains(mouseCoords.x, mouseCoords.y))
                {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        temp = customEvent.squareClickLogic(this->window, &squares[i], track, i);
                    }

                    if (event.mouseButton.button == sf::Mouse::Right) {
                        std::cout << "Right Click" << std::endl;

                        squares[i].changeColor(sf::Color(50, 255, 50));
                    }
                }
            }

            if (temp) {
                // Reset State
                for (int i = 0; i < 64; i++) {
                    squares[i].resetState();
                }

                this->board->setSquares(squares); // Update Board

                std::cout << "Updating Board" << std::endl;

                logic->standbyUpdate();

                logic->updateBoard(this->board); // Update Logic

                //logic->setPlayerTurn();

                this->interface->setTurnCounter(this->interface->useTurnCounter() + 1);
                this->interface->inverseWhite();
            }



        }

    }

}

