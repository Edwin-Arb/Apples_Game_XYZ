#include "Player.h"
#include "Game.h"


namespace Apples_Game
{
    //------------------------------------------------------------------------------------------------------------
    void Init_Player(SPlayer& player, const SGame& game)
    {
        // Init player state
        player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
        player.speed = INITIAL_SPEED;
        player.direction = EPlayer_Direction::EPD_Start_Position;

        // Init player sprite
        player.sprite.setTexture(game.player_Texture);
        Set_Sprite_Relative_Origin(player.sprite, 0.5f, 0.5f);
        Set_Sprite_Size(player.sprite, PLAYER_SIZE, PLAYER_SIZE);

        // Init player Sound(eat, hit)
        player.eat_Sound.setBuffer(game.player_eat_Buffer);
        player.hit_Sound.setBuffer(game.player_hit_Buffer);
    }
    //------------------------------------------------------------------------------------------------------------
    void Set_Player_Direction(SPlayer& player, EPlayer_Direction new_direction)
    {
        player.direction = new_direction;
    }
    //------------------------------------------------------------------------------------------------------------
    void Set_Player_Position(SPlayer& player, const SPosition_2D& new_position)
    {
        player.position = new_position;
    }
    //------------------------------------------------------------------------------------------------------------
    void Update_Player(SPlayer& player, float delta_time)
    {
        // Orient player sprite according to player direction
        switch (player.direction)
        {
            case EPlayer_Direction::EPD_Right:
            {
                player.position.X += player.speed * delta_time;
                player.sprite.setRotation(-90.f);
                break;
            }
            case EPlayer_Direction::EPD_Up:
            {
                player.position.Y -= player.speed * delta_time;
                player.sprite.setRotation(-180.f);
                break;
            }
            case EPlayer_Direction::EPD_Left:
            {
                player.position.X -= player.speed * delta_time;
                player.sprite.setRotation(-270.f);
                break;
            }
            case EPlayer_Direction::EPD_Down:
            {
                player.position.Y += player.speed * delta_time;
                player.sprite.setRotation(0.f);
                break;
            }
            case EPlayer_Direction::EPD_Start_Position:
            {
                player.sprite.setRotation(0.f);
                break;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------
    void Set_Player_Speed(SPlayer& player, float new_speed)
    {
        player.speed = new_speed;
    }
    //------------------------------------------------------------------------------------------------------------
    float Get_Player_Speed(const SPlayer& player)
    {
        return player.speed;
    }
    //------------------------------------------------------------------------------------------------------------
    SRectangle Get_Player_Collider(const SPlayer& player)
    {
        return { { player.position.X - PLAYER_SIZE / 2.f, player.position.Y - PLAYER_SIZE / 2.f },
            { PLAYER_SIZE, PLAYER_SIZE } };
    }
    //------------------------------------------------------------------------------------------------------------
    void Draw_Player(SPlayer& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.X, player.position.Y);
        window.draw(player.sprite);
    }
    //------------------------------------------------------------------------------------------------------------
}