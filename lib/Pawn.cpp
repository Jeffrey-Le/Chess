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
        return;
        }
    if (color == 'b')
    {
        this->isWhite = false;
        this->value *= -1;

        if (!this->texture.loadFromFile("../res/blackPawn.png"))
        {
            // ERROR
            std::cout << "Error Loading Pawn Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        return;
    }

}

Pawn::~Pawn() {

}

bool Pawn::checkFirstMove() {
    if (this->firstMove)
        return true;

    return false;
}

void Pawn::setFirstMove() {
    this->firstMove = false;
}
