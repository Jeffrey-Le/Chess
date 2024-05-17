//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Board.h"

Board::Board() {
    std::cout << "Initializing Board \n";
    this->board = new Bitboard();

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

void Board::updateBoard(Bitboard *latestBoard) {
    this->board = latestBoard;
}

void Board::setSquares(Square *newSquare) {
    this->square = newSquare;
}

void Board::displayBoard() {
    using namespace std;
    //std::cout << std::setw(32) << std::setfill('0') << this->board;
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            cout << endl;
        cout << this->square[i].usePiece();
    }
    cout << endl;
}

uint64_t Board::fullInt(uint64_t numVal) {
    // Display message to user.
    return numVal;
}

void Board::startGame() {
    // Set White Positions
    this->square[63].changePiece(5.0f); // Rook
    this->square[56].changePiece(5.0f); // Rook
    this->square[62].changePiece(3.1f); // Knight
    this->square[57].changePiece(3.1f); // Knight
    this->square[61].changePiece(3.2f); // Bishop
    this->square[58].changePiece(3.2f); // Bishop
    this->square[60].changePiece(9.0f); // Queen
    this->square[59].changePiece(0.1f); // King
    for (int i = 48; i < 56; i++)
        this->square[i].changePiece(1.0f); // Pawn

    // Set Black Positions
    this->square[0].changePiece(-5.0f); // Rook
    this->square[7].changePiece(-5.0f); // Rook
    this->square[1].changePiece(-3.1f); // Knight
    this->square[6].changePiece(-3.1f); // Knight
    this->square[2].changePiece(-3.2f); // Bishop
    this->square[5].changePiece(-3.2f); // Bishop
    this->square[3].changePiece(-9.0f); // Queen
    this->square[4].changePiece(-0.1f); // King
    for (int i = 8; i < 16; i++)
        this->square[i].changePiece(-1.0f); // Pawn
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
