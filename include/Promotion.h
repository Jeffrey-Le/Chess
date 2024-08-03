//
// Created by Jeffrey Vo Le on 7/21/24.
//

#ifndef CHESS_PROMOTION_H
#define CHESS_PROMOTION_H

#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"

class Promotion {
    private:
        sf::RectangleShape *container;
        std::vector<Piece*> pieces;
    public:
        Promotion();
        Promotion(char);
        ~Promotion();

        void drawPromotionUI(sf::Vector2f);

        sf::RectangleShape usePromUI();
        std::vector<Piece*> usePromPieces();
};

#endif //CHESS_PROMOTION_H
