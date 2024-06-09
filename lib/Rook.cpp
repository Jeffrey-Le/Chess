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
        return;
    }
    if (color == 'b')
    {
        this->isWhite = false;
        this->value *= -1;

        if (!this->texture.loadFromFile("../res/blackRook.png"))
        {
            // error...
            std::cout << "Error Loading Knight Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        return;
    }

    //0000000000000000000000000000000000000000000000000000000010000010

}

Rook::~Rook() {

}