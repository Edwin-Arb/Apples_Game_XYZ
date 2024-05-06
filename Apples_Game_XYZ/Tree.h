#pragma once
#include "Constants.h"



namespace Apples_Game
{
    struct STree
    {
        SPosition_2D position;
        sf::Sprite sprite;
    };

    struct SGame;

    void Init_Tree(STree& tree, const SGame &game);
    void Set_Tree_Position(STree &tree, const SPosition_2D &new_position);
    void Draw_Tree(STree& tree, sf::RenderWindow& window);
    SRectangle Get_Tree_Collider(const STree &tree);
}