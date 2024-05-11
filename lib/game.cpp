//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/game.h"

Game::Game() {
    this->window.create(sf::VideoMode(640, 480), "SFML Application");

    this->square = new Square[64];

    for (int i = 0; i < 64; i++) {
        if (i % 2 == 0)
            this->square[i].setColor(sf::Color(255, 255, 255));
        else
            this->square[i].setColor(sf::Color(0, 0, 0));
    }
}

Game::~Game() {
    delete [] this->square;
}

void Game::openGame() {
    std::cout << "In Open Game \n";

    // Draw Variables
    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    bool altRow = false;

    // Set Square Variables
    for (int i = 1; i < 64; i++)
    {
        float oldX = this->square[i-1].usePos().x;
        float oldY = this->square[i-1].usePos().y;

        if (i % 16 == 8)
        {
            altRow = true;
            oldX += 50.0f;
        }

        if (i % 16 == 0)
        {
            altRow = false;
            oldX -= 50.0f;
        }

        if (i % 8 == 0)
            oldY += 50.0f;

        if (altRow)
            oldX *= -1;

        this->square[i].setPos(abs((oldX + 50.0f)), oldY);
    }

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

        // Draw Content
        for (int i = 0; i < 64; i++)
            this->window.draw(this->square[i].useSquare());

        this->window.display(); // Displays
    }
}

