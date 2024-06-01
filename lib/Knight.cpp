//
// Created by Jeffrey Vo Le on 5/17/24.
//

#include "../include/Knight.h"


Knight::Knight() {
    this->value = 3.1f;

    if (!texture.loadFromFile("../res/blackKnight.png"))
    {
        // error...
        std::cout << "Error Loading Knight Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
    this->pieceBoard = new uint64_t(0x4200000000000000);
}

Knight::Knight(char color) {
    this->value = 3.1f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/blackKnight.png"))
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
        if (!this->texture.loadFromFile("../res/blackKnight.png"))
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
