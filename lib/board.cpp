//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/board.h"

Board::Board() {
    std::cout << "Initializing Board \n";
    this->board = new uint64_t(0x008000);
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