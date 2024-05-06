#pragma once
#include "Constants.h"

namespace Apples_Game
{
    struct SApple
    {
        bool is_Eaten_Apple = false;
        SPosition_2D position;
        sf::Sprite sprite;
    };

    struct SGame;

    void Init_Apple(SApple& apples, const SGame &game);
    SCircle Get_Apple_Collider(const SApple &apple);
    void Reset_Apple_State(SApple &apple, const SGame &game);
    void Draw_Apple(SApple& apple, sf::RenderWindow& window);
}
