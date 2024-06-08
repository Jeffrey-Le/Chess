//
// Created by Crolw on 6/7/2024.
//

#include "../include/King.h"


King::King() {
    this->value = 0.1f;

    if (!texture.loadFromFile("../res/whiteKing.png"))
    {
        // error...
        std::cout << "Error Loading Knight Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
    this->pieceBoard = new uint64_t(0x4200000000000000);
}

King::King(char const color) {
    this->value = 0.1f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/whiteKing.png"))
        {
            // error...
            std::cout << "Error Loading Knight Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        this->pieceBoard = new uint64_t(0x4200000000000000);
        return;
    }
    if (color == 'b')
    {
        this->isWhite = false;
        this->value *= -1;

        if (!this->texture.loadFromFile("../res/blackKing.png"))
        {
            // error...
            std::cout << "Error Loading Knight Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        this->pieceBoard = new uint64_t(0x42);
        return;
    }

    //0000000000000000000000000000000000000000000000000000000010000010

    this->pieceBoard = new uint64_t(0);
}

King::~King() {

}