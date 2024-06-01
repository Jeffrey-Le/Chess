//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Board.h"

// Default Constructor
Board::Board() {
    std::cout << "Initializing Board \n";
    this->board = new Bitboard();

    this->square = new Square[64]; // Change to 2d array

    this->font.loadFromFile("../res/arial.ttf");

    this->numPositions = new sf::Text[8];
    this->letterPositions = new sf::Text[8];

    // Initialize Numbers
    for (int i = 0; i < 8; i++)
    {
        this->numPositions[i].setFont(this->font);
        this->numPositions[i].setString(std::to_string(i+1));
        this->numPositions[i].setCharacterSize(30);
    }

    // Initialize Letters
    for (int i = 0; i < 8; i++)
    {
        char const letter = toascii(97 + i);

        //std::cout << letter << std::endl;

        this->letterPositions[i].setFont(this->font);
        this->letterPositions[i].setString(letter);
        this->letterPositions[i].setCharacterSize(30);
    }

}

// Destructor
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

void Board::displayBoard() const {
    // Displays the Piece Value of Each Square on Board
    for (int i = 0; i < 64; i++)
    {
        if (i % 8 == 0)
            std::cout << std::endl;
        std::cout << this->square[i].usePiece();
    }
    std::cout << std::endl;
}

uint64_t Board::fullInt(uint64_t const numVal) {
    // Display message to user.
    return numVal;
}

// Starts a Normal Game
void Board::startGame() const {
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

void Board::drawBoard() const {
    // Default Square
    this->square[0].setPos(50.0f, 50.0f);
    this->square[0].setColor(sf::Color(255, 255, 255, 255));

    bool invertColor = false;

    // Sets Positions and Colors of All Squares on Board
    for (int i = 1; i < 64; i++) {
        sf::Vector2f const oldPos = this->square[i-1].usePos();

        // Set Square Position
        if (i % 8 == 0) {
            sf::Vector2f const leadingSquarePos = this->square[i-8].usePos();
            this->square[i].setPos(leadingSquarePos.x, (leadingSquarePos.y + 50.0f));
            invertColor = !invertColor;
        }
        else
            this->square[i].setPos((oldPos.x + 50.0f), oldPos.y);

        // Set Square Color
        if (invertColor) {
            if (i % 2 == 0)
                this->square[i].setColor(sf::Color(0, 0, 0, 255));
            else
                this->square[i].setColor(sf::Color(255, 255, 255, 255));
        }
        else {
            if (i % 2 == 0)
                this->square[i].setColor(sf::Color(255, 255, 255, 255));
            else
                this->square[i].setColor(sf::Color(0, 0, 0, 255));
        }
    }

    // Sets the Positions of RANKS and FILES of Board
    sf::Vector2f const lastLeadingSq = this->square[56].usePos();

    this->numPositions[0].setPosition(lastLeadingSq.x - 25.0f, lastLeadingSq.y);
    this->letterPositions[0].setPosition((lastLeadingSq.x+15.0f), lastLeadingSq.y + 50.0f);

    for (int i = 1; i < 8; i++)
    {
        sf::Vector2f const numPos = this->numPositions[i-1].getPosition();
        sf::Vector2f const letterPos = this->letterPositions[i-1].getPosition();

        this->numPositions[i].setPosition(numPos.x, numPos.y - 50.0f);
        this->letterPositions[i].setPosition(letterPos.x + 50.0f, letterPos.y);
    }
}

Square *Board::useBoard() const {
    return this->square;
}

sf::Text *Board::usePositions(char const type) const{

    if (type == 'n')
        return this->numPositions;

    if (type == 'l')
        return this->letterPositions;

    std::cout << "ERROR, NO TYPE INPUTTED" << std::endl;
    return nullptr;
}
