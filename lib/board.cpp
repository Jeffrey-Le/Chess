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

    this->font.loadFromFile("/Users/crolwick/Documents/CLionProjects/Chess/res/arial.ttf");

    for (int i = 0; i < 8; i++)
    {
        this->numPositions[i].setFont(this->font);
        this->numPositions[i].setString(std::to_string(i+1));
        this->numPositions[i].setCharacterSize(30);
    }

    for (int i = 0; i < 8; i++)
    {
        char letter = toascii(97 + i);

        std::cout << letter << std::endl;

        this->letterPositions[i].setFont(this->font);
        this->letterPositions[i].setString(letter);
        this->letterPositions[i].setCharacterSize(30);
    }

}

Board::~Board() {
    delete [] this->square;
    delete [] this->numPositions;
    delete [] this->letterPositions;
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

    this->square[0].setPos(50.0f, 50.0f);

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

    float lastSqX = this->square[63].usePos().x;
    float lastSqY = this->square[63].usePos().y;

    std::cout << lastSqY << std::endl;

    this->numPositions[0].setPosition(lastSqX+15.0f, lastSqY + 50.0f);
    this->letterPositions[0].setPosition(lastSqX - 25.0f, lastSqY);

    for (int i = 1; i < 8; i++)
    {
        sf::Vector2f numPos = this->numPositions[i-1].getPosition();
        sf::Vector2f letterPos = this->letterPositions[i-1].getPosition();

        this->numPositions[i].setPosition(numPos.x + 50.0f, numPos.y);
        this->letterPositions[i].setPosition(letterPos.x, letterPos.y - 50.0f);
    }
}

Square *Board::useBoard() {
    return this->square;
}

sf::Text *Board::usePositions(char type) {

    if (type == 'n')
        return this->numPositions;

    if (type == 'l')
        return this->letterPositions;

    return nullptr;
}
