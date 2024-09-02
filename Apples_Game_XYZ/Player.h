#pragma once
#include "Constants.h"

namespace Apples_Game
{
    enum class EPlayer_Direction : int
    {
        EPD_Right = 0,
        EPD_Up,
        EPD_Left,
        EPD_Down,

        EPD_Start_Position
    };

    struct SPlayer
    {
        // Init state player
        float speed = INITIAL_SPEED;
        SPosition_2D position;
        EPlayer_Direction direction = EPlayer_Direction::EPD_Start_Position;

        // Init Texture in player
        sf::Sprite sprite;

        // Init Sounds
        sf::Sound eat_Sound;
        sf::Sound hit_Sound;
    };

    struct  SGame;

    void Init_Player(SPlayer& player, const SGame& game);
    void Set_Player_Direction(SPlayer &player, EPlayer_Direction new_direction);
    void Set_Player_Position(SPlayer& player, const SPosition_2D& new_position);
    void Set_Player_Speed(SPlayer& player, float new_speed);
    void Update_Player(SPlayer& player, float delta_time);
    //float Get_Player_Speed(const SPlayer& player);
    
    SRectangle Get_Player_Collider(const SPlayer &player);
    void Draw_Player(SPlayer& player, sf::RenderWindow& window);
}