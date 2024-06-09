//
// Created by Jeffrey Vo Le on 5/17/24.
//

#include "../include/Knight.h"


Knight::Knight() {
    this->value = 3.1f;

    if (!texture.loadFromFile("../res/whiteKnight.png"))
    {
        // error...
        std::cout << "Error Loading Knight Texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
}

Knight::Knight(char const color) {
    this->value = 3.1f;

    if (color == 'w')
    {
        if (!this->texture.loadFromFile("../res/whiteKnight.png"))
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

        if (!this->texture.loadFromFile("../res/blackKnight.png"))
        {
            // error...
            std::cout << "Error Loading Knight Texture" << std::endl;
        }

        this->sprite.setTexture(this->texture);
        return;
    }

    //0000000000000000000000000000000000000000000000000000000010000010

}
