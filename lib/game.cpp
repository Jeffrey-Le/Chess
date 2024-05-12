//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/game.h"

Game::Game() {
    this->window.create(sf::VideoMode(640, 480), "SFML Application");

    this->board = new Board(); // Create a new board
}

Game::~Game() {
    delete this->board;
}

void Game::openGame() {
    std::cout << "In Open Game \n";

    // Draw Variables
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    this->board->drawBoard(); // Setup square board elements


    while (this->window.isOpen())
    {
        sf::Event event; // Event

        // Event to check when user attempts to close window
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }

        this->window.clear(sf::Color(sf::Color(0, 255, 0))); // Clears Canvas

        // Draw Content onto Window
//        for (int i = 0; i < 64; i++)
//            this->window.draw(this->board->useBoard()[i].useSquare());

        this->window.draw(this->board->usePositions()[1]);

        this->window.display(); // Display
    }

}

