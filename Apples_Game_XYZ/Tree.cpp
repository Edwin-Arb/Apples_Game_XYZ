#include "Tree.h"
#include "Game.h"

namespace Apples_Game
{
    //--------------------------------------------------------------------------------------------------------
    void Init_Tree(STree& tree, const SGame& game)
    {
        // Init tree Shape
        tree.sprite.setTexture(game.tree_Texture);
        Set_Sprite_Size(tree.sprite, TREE_SIZE, TREE_SIZE);
        Set_Sprite_Relative_Origin(tree.sprite, 0.5f, 0.5f);
    }
    //--------------------------------------------------------------------------------------------------------
    void Set_Tree_Position(STree &tree, const SPosition_2D &new_position)
    {
        tree.position = new_position;
    }
    //--------------------------------------------------------------------------------------------------------
    void Draw_Tree(STree& tree, sf::RenderWindow& window)
    {
        tree.sprite.setPosition(tree.position.X, tree.position.Y);
        window.draw(tree.sprite);
    }
    //--------------------------------------------------------------------------------------------------------
    SRectangle Get_Tree_Collider(const STree& tree)
    {
        return { { tree.position.X - TREE_SIZE / 2.f, tree.position.Y - TREE_SIZE / 2.f },
                      { TREE_SIZE, TREE_SIZE } };
    }
    //--------------------------------------------------------------------------------------------------------
}
