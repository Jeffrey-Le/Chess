//
// Created by Crolw on 6/7/2024.
//

#include "../include/Bishop.h"

Bishop::Bishop() {
    this->value = 3.2f;

    if (!texture.loadFromFile("../res/whiteBishop.png"))
    {
        // error...
        std::cout << "Error Loading Knight Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
}

Bishop::Bishop(char const color) {
    this->value = 3.2f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/whiteBishop.png"))
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

        if (!this->texture.loadFromFile("../res/blackBishop.png"))
        {
            // error...
            std::cout << "Error Loading Knight Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        return;
    }

    //0000000000000000000000000000000000000000000000000000000010000010

}

Bishop::~Bishop() {

}