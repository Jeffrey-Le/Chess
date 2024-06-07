//
// Created by Jeffrey Vo Le on 5/11/24.
//

#include "../include/Pawn.h"

Pawn::Pawn() {
    this->value = 1.0f;

    if (!texture.loadFromFile("../res/whitePawn.png"))
    {
        // error...
        std::cout << "Error Loading Pawn Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
    this->pieceBoard = new uint64_t(0x00ff000000000000);
}

Pawn::Pawn(char const color) {
    this->value = 1.0f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/whitePawn.png"))
        {
            // ERROR
            std::cout << "Error Loading Pawn Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        this->pieceBoard = new uint64_t(0x00ff000000000000);
        return;
        }
    if (color == 'b')
    {
        if (!this->texture.loadFromFile("../res/blackPawn.png"))
        {
            // ERROR
            std::cout << "Error Loading Pawn Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        this->pieceBoard = new uint64_t(0x000000000000ff00);
        return;
    }

    this->pieceBoard = new uint64_t(0);
}