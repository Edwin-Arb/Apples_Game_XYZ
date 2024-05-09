#include "Math.h"
#include <random>
#include "Player.h"
#include "Apple.h"
#include "Game.h"


namespace Apples_Game
{
    //------------------------------------------------------------------------------------------------------------
    bool Do_Shapes_Collide(const SRectangle& rect_1, const SRectangle& rect_2)
    {
        return (rect_1.position.X < rect_2.position.X + rect_2.size.X) &&
               (rect_1.position.X + rect_1.size.X > rect_2.position.X) &&
               (rect_1.position.Y < rect_2.position.Y + rect_2.size.Y) &&
               (rect_1.position.Y + rect_1.size.Y > rect_2.position.Y);
    }
    //------------------------------------------------------------------------------------------------------------
    bool Do_Shapes_Collide(const SRectangle& rect, const SCircle& circle)
    {
        const float delta_x = circle.position.X - std::max(rect.position.X, std::min(circle.position.X, rect.position.X + rect.size.X));
        const float delta_y = circle.position.Y - std::max(rect.position.Y, std::min(circle.position.Y, rect.position.Y + rect.size.Y));
        
        return (delta_x * delta_x + delta_y * delta_y) < (circle.radius * circle.radius);
    }
    //------------------------------------------------------------------------------------------------------------
    bool Do_Shapes_Collide(const SCircle& circle_1, const SCircle& circle_2)
    {
        const float delta_x = circle_1.position.X - circle_2.position.X;
        const float delta_y = circle_1.position.Y - circle_2.position.Y;
        const float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        
        return (distance < circle_1.radius + circle_2.radius);
    }
    //------------------------------------------------------------------------------------------------------------
    void Check_Collision_With_Apples(SGame& game)
    {
        // Get player collider
        SRectangle player_Collider = Get_Player_Collider(game.player);
        
        // Create a vector to hold the indexes of the apples that need to be removed
        std::vector<size_t> apples_to_delete;
        
        // Loop for checking apples on a map
        for (size_t i = 0; i < game.apples_array.size(); ++i)
        {
            // Get an apple collider
            SCircle apple_Collider = Get_Apple_Collider(game.apples_array[i]);
        
            // Check collision between player and apple
            if (Do_Shapes_Collide(player_Collider, apple_Collider))
            {
                // Endless Apples Mode
                if (game.game_Mode & BIT_ENDLESS_APPLES_MODE)
                {
                    // Set a new position for the apple
                    Reset_Apple_State(game.apples_array[i], game);
                }
                else
                {
                    // Marking an apple for removal
                    apples_to_delete.emplace_back(i);
                }

                // Acceleration Mode
                if (game.game_Mode & BIT_ACCELERATION_MODE)
                {
                    game.player.speed += ACCELERATION;
                }
        
                game.count_Eaten_Apples += 4;
                game.player.eat_Sound.play();
            }
        }
        
        // Remove marked apples from vector
        for (auto it = apples_to_delete.rbegin(); it != apples_to_delete.rend(); ++it)
        {
            game.apples_array.erase(game.apples_array.begin() + static_cast<size_t>(*it));
        }
    }
    //------------------------------------------------------------------------------------------------------------
    // For random generation of objects
    SPosition_2D Get_Random_Position_In_Screen(const SRectangle &rect)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> result_X(rect.position.X, rect.position.X + rect.size.X);
        std::uniform_real_distribution<float> result_Y(rect.position.Y, rect.position.Y + rect.size.Y);

        return {result_X(gen), result_Y(gen)};
    }
    //------------------------------------------------------------------------------------------------------------
    void Set_Sprite_Size(sf::Sprite& sprite, const float desired_Width, const float desired_Height)
    {
        const sf::FloatRect sprite_Rect = sprite.getLocalBounds();
        const sf::Vector2f scale = { desired_Width / sprite_Rect.width, desired_Height / sprite_Rect.height };
        sprite.setScale(scale);
    }
    //------------------------------------------------------------------------------------------------------------
    void Set_Sprite_Relative_Origin(sf::Sprite& sprite, const float origin_X, const float origin_Y)
    {
        const sf::FloatRect sprite_Rect = sprite.getLocalBounds();
        sprite.setOrigin(origin_X * sprite_Rect.width, origin_Y * sprite_Rect.height);
    }
    //------------------------------------------------------------------------------------------------------------
    int Get_Random_Int(const int &min,const int &max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(gen);
    }
    //------------------------------------------------------------------------------------------------------------
}