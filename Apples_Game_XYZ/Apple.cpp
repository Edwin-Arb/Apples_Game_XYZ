#include "Apple.h"
#include "Game.h"


namespace Apples_Game
{
    //--------------------------------------------------------------------------------------------------------
    void Init_Apple(SApple& apples, const SGame& game)
    {
        // Init apple Shape
        apples.sprite.setTexture(game.apple_Texture);
        Set_Sprite_Size(apples.sprite, APPLE_SIZE, APPLE_SIZE);
        Set_Sprite_Relative_Origin(apples.sprite, 0.5f, 0.5f);
    }
    //--------------------------------------------------------------------------------------------------------
    SCircle Get_Apple_Collider(const SApple& apple)
    {
        return {apple.position, APPLE_SIZE / 2.f};
    }
    //--------------------------------------------------------------------------------------------------------
    void Reset_Apple_State(SApple& apple, const SGame& game)
    {
        apple.is_Eaten_Apple = false;
        apple.position = Get_Random_Position_In_Screen(game.screen_Rect);
    }
    //--------------------------------------------------------------------------------------------------------
    void Draw_Apple(SApple& apple, sf::RenderWindow& window)
    {
        apple.sprite.setPosition(apple.position.X, apple.position.Y);
        window.draw(apple.sprite);
    }
    //--------------------------------------------------------------------------------------------------------
}
