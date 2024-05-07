#pragma once
#include "Constants.h"

// Table row height
constexpr float ROW_HEIGHT = 30.f;

// Show only the first seven players
constexpr int MAX_PLAYERS_TO_DISPLAY = 7;

// SLeaderboard
struct SLeaderboard
{
    string name;
    int score;
};

namespace Apples_Game
{
    struct SUser_Interface
    {
        bool is_GameOver_Text_Visible = false;
        bool is_Draw_Pause_Buttons = true;
        
        vector<SLeaderboard> vector_Score_Table
        {
                {"Edwin", 0}, {"Remuro", 0}, {"Vanitas", 0}, {"Ahmed", 0}, {"Vanessa", 0},
                {"Anton", 0}, {"Laffolia", 0},{"Miron", 0}, {"Lanaya", 0}, {"YOU", 0}
        };
        
        sf::Font font;
        sf::Text text_Score;
        sf::Text text_Random_Number_Apples_Mode;
        sf::Text text_Endless_Apples_Mode;
        sf::Text text_Acceleration_Mode;
        sf::Text text_GameOver;
        sf::Text text_Menu;
        sf::Text text_Pause;
        sf::Text text_Continue;
        sf::Text text_Exit;
        sf::Text text_Information;
        sf::Text text_Player_Name;
        sf::Text text_Leaderboard_Name[SIZE_LEADERBOARD];
    };

    void Init_User_Interface(SUser_Interface& ui_state);
    void Init_Text(sf::Text& text, const sf::Font& font, sf::Color color,
                   int size, float position_x, float position_y,
                   float offset_x = 0.f, float offset_y = 0.f, const string &name = "NON");
    
    void Init_Text_Leaderboard(SGame& game, vector<SLeaderboard> &score_table, float row_height, float vertical_spacing, float origin_x, float origin_y);
    void Draw_User_Interface(SUser_Interface& ui_state, struct SGame& game, sf::RenderWindow& window);
}
