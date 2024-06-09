//
// Created by Crolw on 6/7/2024.
//

#include "../include/Queen.h"


Queen::Queen() {
    this->value = 9.0f;

    if (!texture.loadFromFile("../res/whiteQueen.png"))
    {
        // error...
        std::cout << "Error Loading Knight Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
}

Queen::Queen(char const color) {
    this->value = 9.0f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/whiteQueen.png"))
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

        if (!this->texture.loadFromFile("../res/blackQueen.png"))
        {
            // error...
            std::cout << "Error Loading Knight Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        return;
    }

    //0000000000000000000000000000000000000000000000000000000010000010

}

Queen::~Queen() {

}