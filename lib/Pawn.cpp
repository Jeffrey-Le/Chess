//
// Created by Jeffrey Vo Le on 5/11/24.
//

#include "../include/Pawn.h"

Pawn::Pawn() {
    this->value = 1;

    if (!texture.loadFromFile("/Users/crolwick/Documents/CLionProjects/Chess/res/blackKing.png"))
    {
        // error...
        std::cout << "Error Loading Pawn Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);

    this->pieceBoard = new uint64_t(0x00ff000000000000);
}

Pawn::Pawn(char color) {
    this->value = 1;

    if (color == 'w')
    {
        if (!texture.loadFromFile("/Users/crolwick/Documents/CLionProjects/Chess/res/whitePawn.png"))
        {
            // error...
            std::cout << "Error Loading Pawn Texture" << std::endl;
        }

        this->pieceBoard = new uint64_t(0x00ff000000000000);
        return;
        }
    if (color == 'b')
    {
        if (!texture.loadFromFile("/Users/crolwick/Documents/CLionProjects/Chess/res/blackPawn.png"))
        {
            // error...
            std::cout << "Error Loading Pawn Texture" << std::endl;
        }

        this->pieceBoard = new uint64_t(0x000000000000ff00);
        return;
    }

    this->pieceBoard = new uint64_t(0);
}