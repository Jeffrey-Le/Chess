//
// Created by Crolw on 6/7/2024.
//

#include "../include/Rook.h"


Rook::Rook() {
    this->value = 5.0f;

    if (!texture.loadFromFile("../res/whiteRook.png"))
    {
        // error...
        std::cout << "Error Loading Knight Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
    this->pieceBoard = new uint64_t(0x4200000000000000);
}

Rook::Rook(char const color) {
    this->value = 5.0f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/whiteRook.png"))
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
        this->value *= -1;

        if (!this->texture.loadFromFile("../res/blackRook.png"))
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

Rook::~Rook() {

}