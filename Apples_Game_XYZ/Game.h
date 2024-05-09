#pragma once
#include <vector>
#include "Player.h"
#include "Apple.h"
#include "Tree.h"
#include "User_Interface.h"

namespace Apples_Game
{
    // Create game objects
    struct SGame
    {
        // Game state
        bool is_Screen_Menu = true;
        bool is_Screen_Pause = false;
        bool is_Screen_Game_Over = false;
        bool is_Leaderboard = false;

        // User for Bit Mask
        int game_Mode = 0;
        
        int number_Apples = 0;
        int count_Eaten_Apples = 0;
        float time_Since_Game_Finish = 0.f;

        SRectangle screen_Rect;
        
        // Init Objects state
        SPlayer player;
        vector<SApple> apples_array;
        vector<STree> trees_array;
        SUser_Interface ui_state;
        sf::RectangleShape background;

        // Game resources path
        sf::Texture player_Texture;
        sf::Texture apple_Texture;
        sf::Texture tree_Texture;

        // Init game map
        sf::RenderTexture pause_blur_Texture;
        sf::Sprite pause_blur_Sprite;
        sf::Texture game_map_Image;
        sf::Sprite game_map_Sprite;
        
        // Init Audio
        sf::SoundBuffer player_eat_Buffer;
        sf::SoundBuffer player_hit_Buffer;
        sf::SoundBuffer player_is_died_Buffer;
        sf::Sound player_Sound;

        // Mouse
        sf::Vector2i mouse_Position;
    };
    
    void Init_Game(SGame& game);
    void Update_Game(SGame& game, const float delta_time);

    void Start_Playing_State(SGame &game);
    void Update_Playing_State(SGame &game, const float delta_time);
    
    void Start_GameOver_State(SGame& game);
    void Update_GameOver_State(SGame& game, const float delta_time);
    
    void Update_Menu(SGame &game, const float delta_time);
    
    void Handle_Keys_Main_Menu(const sf::Event& event, sf::RenderWindow &window, SGame& game);
    void Toggle_Game_Mode(SGame &game, const int mode_selection);
    string Get_Button_Text(const SGame &game, const int mode_selection);
    void Draw_Game(SGame& game, sf::RenderWindow& window);
    void Deinitialize_Game(SGame& game);
}