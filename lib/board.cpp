//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/board.h"

Board::Board() {
    std::cout << "Initializing Board \n";
    this->board = new uint64_t(0x008000);

    this->square = new Square[64];

    this->numPositions = new sf::Text[8];
    this->letterPositions = new sf::Text[8];

    for (int i = 0; i < 64; i++) {
        if (i % 2 == 0)
            this->square[i].setColor(sf::Color(255, 255, 255));
        else
            this->square[i].setColor(sf::Color(0, 0, 0));
    }

    sf::Font font;

    font.loadFromFile("/Users/crolwick/Documents/CLionProjects/Chess/res/arial.ttf");

    for (int i = 0; i < 8; i++)
    {
        this->numPositions[i].setFont(font);
        this->numPositions[i].setString(std::to_string(i+1));
        this->numPositions[i].setCharacterSize(10);

        char letter = toascii(97 + i);

        std::cout << letter << std::endl;

        this->letterPositions[i].setFont(font);
        this->letterPositions[i].setString(letter);
        this->letterPositions[i].setCharacterSize(10);
    }

}

Board::~Board() {
    delete [] this->square;
}

void Board::updateBoard(uint64_t *latestBoard) {
    this->board = latestBoard;
}

void Board::displayBoard() {
    std::cout << std::setw(32) << std::setfill('0') << this->board;
}

uint64_t Board::fullInt(uint64_t numVal) {
    // Display message to user.
    return numVal;
}

void Board::drawBoard() {

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
}

Square *Board::useBoard() {
    return this->square;
}

sf::Text *Board::usePositions() {
    return this->numPositions;
}
