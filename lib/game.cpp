//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/game.h"

Game::Game() {
    this->window.create(sf::VideoMode(640, 480), "SFML Application");
}

void Game::openGame() {
    std::cout << "In Open Game \n";

    // Draw Variables
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    while (this->window.isOpen())
    {
        sf::Event event; // Event

        // Event to check when user attempts to close window
        while (this->window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->window.close();
        }

        this->window.clear(); // Clears Canvas

        // Draw Content
        this->window.draw(shape);

        this->window.display(); // Displays
    }
}