//
// Created by Jeffrey Vo Le on 5/10/24.
//

#include "../include/Piece.h"


Piece::Piece() {
    this->value = 0;
}


Piece::Piece(bool isWhite) {
    this->value = 0;
    this->isWhite = isWhite;
}

void Piece::setPosition(float x, float y) {
    this->sprite.setPosition(x, y);
}

void Piece::setValue(float const newValue) {
    this->value = newValue;
}

void Piece::setTexture(sf::Texture const &newTextureObj) {
    this->texture = newTextureObj;
    this->sprite.setTexture(this->texture);
}

void Piece::setTexture(std::string const &pathToTexture) {
    if (!this->texture.loadFromFile(pathToTexture)) {
        std::cout << "Error Loading New Texture from file path:" << std::endl << pathToTexture << std::endl;
        return;
    }

    this->sprite.setTexture(this->texture);
}


sf::Sprite Piece::useSprite() {
//    if (!this->sprite.getTexture())
//    {
//        std::cout << "No Texture Loaded" << std::endl;
//    }

    return this->sprite;
}

float Piece::useVal() const{
    return this->value;
}

bool Piece::checkWhite() {
    if (this->isWhite)
        return true;

    return false;
}
