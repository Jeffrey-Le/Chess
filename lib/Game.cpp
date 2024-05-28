//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Game.h"
#include "../include/CustomEvent.h"

Game::Game() {
    this->window.create(sf::VideoMode(960, 720), "SFML Application");

    this->board = new Board(); // Create a new board

    this->myMouse = new sf::Mouse();
}

Game::~Game() {
    delete this->board;
}

void Game::openGame() {
    std::cout << "In Open Game \n";

    // Draw Variables
    this->board->drawBoard(); // Setup square board elements

    this->board->startGame();

    //this->board->displayBoard();

    GameLogic *test = new GameLogic(*this->board);

    Square *squares = this->board->useBoard();

    Piece *track = nullptr;

    std::cout << "Track Initalized: " << track << std::endl;

    CustomEvent customEvent;

    while (this->window.isOpen())
    {
        sf::Event event = customEvent.useCustomEvent();
        //sf::Event event; // CustomEvent

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

        this->window.display(); // Display


        // CustomEvent to check when user attempts to close window
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {

                if (event.mouseButton.button == sf::Mouse::Left) {
                    track = customEvent.squareClickLogic(this->window, squares, track);

                    if (track != nullptr) {
                        std::cout << "Outside: " << track << std::endl;
                    }
                    else
                        std::cout << "NullPTR" << std::endl;
                }
            }

        }

    }

}

