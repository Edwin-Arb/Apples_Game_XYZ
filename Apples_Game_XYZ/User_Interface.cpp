#include "User_Interface.h"
#include "Game.h"
#include <random>


namespace Apples_Game
{
    //--------------------------------------------------------------------------------------------------------
    void Init_User_Interface(SUser_Interface& ui_state, SGame& game)
    {
        // Init Font
        ui_state.font.loadFromFile(RESOURCES_PATH + "Fonts/Pirate.ttf");

        // Score
        Init_Text(ui_state.text_Score, ui_state.font, sf::Color::Blue,
                  30, 10.f, 10.f);

        // Start Setting
        Init_Text(ui_state.text_Random_Number_Apples_Mode, ui_state.font, sf::Color::Magenta,
                  30, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f,
                  160.f);

        // Acceleration mode                                                           
        Init_Text(ui_state.text_Acceleration_Mode, ui_state.font, sf::Color::Magenta,
                  30, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f,
                  160.f, -30.f);

        // Endless apples mode                                                         
        Init_Text(ui_state.text_Endless_Apples_Mode, ui_state.font, sf::Color::Magenta,
                  30, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 100.f,
                  160.f, -60.f);

        // GameOver
        Init_Text(ui_state.text_GameOver, ui_state.font, sf::Color::Yellow,
                  130, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,
                  290.f, 250.f, "GameOver");

        // Menu
        Init_Text(ui_state.text_Menu, ui_state.font, sf::Color::Yellow,
                  160, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,
                  235.f, 330.f, "Apples");

        // Pause
        Init_Text(ui_state.text_Pause, ui_state.font, sf::Color::Yellow,
                  160, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,
                  200.f, 300.f, "Pause");

        // Pause "Continue button" 
        Init_Text(ui_state.text_Continue, ui_state.font, sf::Color::White,
                  70, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,
                  130.f, 50.f, "Continue");

        // Pause "Exit button" 
        Init_Text(ui_state.text_Exit, ui_state.font, sf::Color::White,
                  70, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,
                  55.f, -85.f, "Exit");

        // User information
        Init_Text(ui_state.text_Information, ui_state.font, sf::Color::White,
                  30, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f,
                  150.f, 110.f, "press Space to continue");

        // Leaderboard
        for (SLeaderboard& item : ui_state.vector_Score_Table)
        {
            if (item.name == "YOU")
            {
                item.score = 0;
            }
            else
            {
                item.score = Get_Random_Int(NUM_APPLES_MIN, NUM_APPLES_MAX);
            }
        }
    }
    //--------------------------------------------------------------------------------------------------------
    void Init_Text(sf::Text& text, const sf::Font& font, sf::Color color,
                  int size, float position_x, float position_y,
                  float offset_x, float offset_y, const string& name)
    {
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(sf::Color(color));
        text.setPosition(position_x, position_y);
        text.setOrigin(offset_x, offset_y);
        text.setString(name);
    }
    //--------------------------------------------------------------------------------------------------------
    void Init_Text_Leaderboard(SGame& game, vector<SLeaderboard>& score_table, float row_height, float vertical_spacing,
                               float origin_x, float origin_y)
    {
        int i = 0;
        float vertical_position = 0.f;

        // Sort vector Score Table
        stable_sort(game.ui_state.vector_Score_Table.begin(), game.ui_state.vector_Score_Table.end(),
                    [](const SLeaderboard& a, const SLeaderboard& b)
                    {
                        return a.score > b.score;
                    });

        // Init text
        for (SLeaderboard& item : score_table)
        {
            if (item.name == "YOU")
            {
                Init_Text(game.ui_state.text_Leaderboard_Name[i], game.ui_state.font, sf::Color::White,
                          40, SCREEN_WIDTH / 2.f, vertical_position);
                if (item.score < game.count_Eaten_Apples)
                {
                    item.score = game.count_Eaten_Apples;
                }
            }
            else
            {
                Init_Text(game.ui_state.text_Leaderboard_Name[i], game.ui_state.font, sf::Color::Green,
                          40, SCREEN_WIDTH / 2.f, vertical_position);
            }

            game.ui_state.text_Leaderboard_Name[i].setString(item.name + ": " + to_string(item.score));
            game.ui_state.text_Leaderboard_Name[i].setOrigin(origin_x, origin_y);

            vertical_position += row_height + vertical_spacing;
            ++i;
        }
    }
    //--------------------------------------------------------------------------------------------------------
    void Draw_User_Interface(SUser_Interface& ui_state, struct SGame& game, sf::RenderWindow& window)
    {
        // Init pause texture
        game.pause_blur_Texture.create(window.getSize().x, window.getSize().y);
        game.pause_blur_Texture.clear(sf::Color(0, 0, 0, 180));
        game.pause_blur_Sprite.setTexture(game.pause_blur_Texture.getTexture());

        // Draw Start setting
        ui_state.text_Random_Number_Apples_Mode.setString(
            "Random number apples: " + string(Get_Button_Text(game, BIT_RANDOM_APPLES_MODE)));
        ui_state.text_Acceleration_Mode.setString(
            "Acceleration Mode: " + string(Get_Button_Text(game, BIT_ACCELERATION_MODE)));
        ui_state.text_Endless_Apples_Mode.setString(
            "Endless Mode: " + string(Get_Button_Text(game, BIT_ENDLESS_APPLES_MODE)));

        // Draw screen "Menu"
        if (game.is_Screen_Menu == true)
        {
            // Menu
            window.draw(ui_state.text_Menu);
            window.draw(ui_state.text_Information);

            // Buttons Mode
            window.draw(ui_state.text_Random_Number_Apples_Mode);
            window.draw(ui_state.text_Acceleration_Mode);
            window.draw(ui_state.text_Endless_Apples_Mode);
        }

        // Draw screen "Pause"
        if (game.is_Screen_Pause == true)
        {
            // Blur screen
            window.draw(game.pause_blur_Sprite);

            // Buttons
            window.draw(ui_state.text_Pause);

            if (ui_state.is_Draw_Pause_Buttons == true)
            {
                window.draw(ui_state.text_Continue);
                window.draw(ui_state.text_Exit);
            }
        }

        // Draw Leaderboard
        if (game.is_Leaderboard == true)
        {
            // Blur screen
            if (game.is_Screen_Pause == false)
            {
                window.draw(game.pause_blur_Sprite);
            }

            // Score table
            Init_Text_Leaderboard(game, ui_state.vector_Score_Table, ROW_HEIGHT, 10, 100, -220);

            // Draw
            for (int i = 0; i < MAX_PLAYERS_TO_DISPLAY; ++i)
            {
                window.draw(ui_state.text_Leaderboard_Name[i]);
            }
        }

        // Draw screen "GameOver"
        ui_state.is_GameOver_Text_Visible = game.is_Screen_Game_Over;
        if (ui_state.is_GameOver_Text_Visible == true)
        {
            // GameOver
            window.draw(ui_state.text_GameOver);
            window.draw(ui_state.text_Information);

            // Buttons Mode
            window.draw(ui_state.text_Random_Number_Apples_Mode);
            window.draw(ui_state.text_Acceleration_Mode);
            window.draw(ui_state.text_Endless_Apples_Mode);
        }

        // Draw Score
        ui_state.text_Score.setString("Score: " + to_string(game.count_Eaten_Apples));
        window.draw(game.ui_state.text_Score);
    }
    //--------------------------------------------------------------------------------------------------------
}
