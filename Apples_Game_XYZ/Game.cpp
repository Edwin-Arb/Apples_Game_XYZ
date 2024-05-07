#include "Game.h"
#include <cassert>


namespace Apples_Game
{
    //------------------------------------------------------------------------------------------------------------
    void Start_Playing_State(SGame& game)
    {
        // Init player state
        Set_Player_Position(game.player, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});
        Set_Player_Direction(game.player, EPlayer_Direction::EPD_Start_Position);
        Set_Player_Speed(game.player, INITIAL_SPEED);

        // Init the number of apples in the game
        if (game.game_Mode & BIT_RANDOM_APPLES_MODE)
        {
            game.number_Apples = Get_Random_Int(NUM_APPLES_MIN, NUM_APPLES_MAX);
        }
        else
        {
            game.number_Apples = NUM_APPLES_MAX / 2;
        }

        // Init apples state
        game.apples_array.resize(NUM_APPLES_MAX);
        for (int i = 0; i < game.number_Apples; ++i)
        {
            SApple apple;
            apple.position = Get_Random_Position_In_Screen(game.screen_Rect);
            Init_Apple(apple, game);
            Reset_Apple_State(apple, game);
            game.apples_array.push_back(apple);
        }
        
        // Init position a tree
        for (auto& tree_count : game.trees_array)
        {
            Set_Tree_Position(tree_count, Get_Random_Position_In_Screen(game.screen_Rect));
        }

        // Set default parameters
        game.is_Screen_Game_Over = false;
        game.count_Eaten_Apples = 0;
        game.time_Since_Game_Finish = 0;
    }

    //------------------------------------------------------------------------------------------------------------
    void Update_Playing_State(SGame& game, float delta_time)
    {
        // Handle input
        if (game.is_Screen_Pause == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                game.player.direction = EPlayer_Direction::EPD_Right;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                game.player.direction = EPlayer_Direction::EPD_Up;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                game.player.direction = EPlayer_Direction::EPD_Left;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                game.player.direction = EPlayer_Direction::EPD_Down;
            }
        }

        // Update player direction and sprite
        if (game.is_Screen_Pause == false)
        {
            Update_Player(game.player, delta_time);
        }

        // Check screen borders collision
        if (Do_Shapes_Collide(Get_Player_Collider(game.player), game.screen_Rect) == false)
        {
            Start_GameOver_State(game);
        }

        // Check collision with an apple
        Check_Collision_With_Apples(game);

        // Check collision with a tree
        for (auto& tree_count : game.trees_array)
        {
            if (Do_Shapes_Collide(Get_Player_Collider(game.player), Get_Tree_Collider(tree_count)) == true)
            {
                Start_GameOver_State(game);
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------
    void Start_GameOver_State(SGame& game)
    {
        game.is_Screen_Game_Over = true;
        game.is_Screen_Menu = false;
        game.time_Since_Game_Finish = 0.f;
        game.player.hit_Sound.play();
        game.player_Sound.play();
    }
    //------------------------------------------------------------------------------------------------------------
    void Update_GameOver_State(SGame& game, float delta_time)
    {
        // Check the pause length and set the Background color to Red.
        if (game.time_Since_Game_Finish <= PAUSE_LENGTH)
        {
            game.time_Since_Game_Finish += delta_time;
            game.background.setFillColor(sf::Color::Red);
            game.player.hit_Sound.play();
            game.player_Sound.play();
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                game.background.setFillColor(sf::Color::Black);
                game.player_Sound.stop();
                Start_Playing_State(game);
                game.is_Screen_Game_Over = false;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------
    void Update_Menu(SGame& game, const float delta_time)
    {
        // Check the pause length and set the Background color to Blue.
        if (game.time_Since_Game_Finish <= PAUSE_LENGTH)
        {
            game.time_Since_Game_Finish += delta_time;
            game.background.setFillColor(sf::Color::Blue);
        }
        else
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                game.background.setFillColor(sf::Color::Black);
                Start_Playing_State(game);
                game.is_Screen_Menu = false;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------
    void Init_Game(SGame& game)
    {
        // Init Texture objects
        assert(game.player_Texture.loadFromFile(RESOURCES_PATH + "Boar_XYZ.png"));
        assert(game.apple_Texture.loadFromFile(RESOURCES_PATH + "Apple_XYZ.png"));
        assert(game.tree_Texture.loadFromFile(RESOURCES_PATH + "Tree_XYZ.png"));

        // Init Audio
        assert(game.player_eat_Buffer.loadFromFile(RESOURCES_PATH + "Boar_Eat_Sound.wav"));
        assert(game.player_hit_Buffer.loadFromFile(RESOURCES_PATH + "Boar_Hit_Sound.wav"));
        assert(game.player_is_died_Buffer.loadFromFile(RESOURCES_PATH + "Boar_Die_Sound.wav"));
        game.player.hit_Sound.setVolume(20.f);
        game.player_Sound.setBuffer(game.player_is_died_Buffer);
        game.player_Sound.setVolume(5.f);

        // Init game map
        assert(game.game_map_Image.loadFromFile(RESOURCES_PATH + "Background_Grass_XYZ.jpg"));
        game.game_map_Sprite.setTexture(game.game_map_Image);
        game.game_map_Sprite.setPosition(0.f, 0.f);

        // Init game objects
        game.screen_Rect = {{0.f, 0.f}, {SCREEN_WIDTH, SCREEN_HEIGHT}};

        // Init player state
        Init_Player(game.player, game);

        // Init rocks state
        for (auto& tree_count : game.trees_array)
        {
            Init_Tree(tree_count, game);
        }

        // Init ui_state
        Init_User_Interface(game.ui_state, game);

        // Init background Shape
        game.background.setFillColor(sf::Color::Red);
        game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        game.background.setPosition(0.f, 0.f);

        Start_Playing_State(game);
    }
    //------------------------------------------------------------------------------------------------------------
    void Update_Game(SGame& game, float delta_time)
    {
        // Update game state
        if (game.is_Screen_Menu == true)
        {
            Update_Menu(game, delta_time);
        }
        else if (game.is_Screen_Game_Over == false)
        {
            Update_Playing_State(game, delta_time);
        }
        else if (game.is_Screen_Game_Over == true)
        {
            Update_GameOver_State(game, delta_time);
        }
    }
    //------------------------------------------------------------------------------------------------------------
    void Handle_Keys_Main_Menu(const sf::Event& event, sf::RenderWindow& window, SGame& game)
    {
        // RANDOM_APPLES_MODE
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
        {
            Toggle_Game_Mode(game, BIT_RANDOM_APPLES_MODE);
            Get_Button_Text(game, BIT_RANDOM_APPLES_MODE);
        }

        // ACCELERATION_MODE
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
        {
            Toggle_Game_Mode(game, BIT_ACCELERATION_MODE);
            Get_Button_Text(game, BIT_ACCELERATION_MODE);
        }

        // ENDLESS_APPLES_MODE
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
        {
            Toggle_Game_Mode(game, BIT_ENDLESS_APPLES_MODE);
            Get_Button_Text(game, BIT_ENDLESS_APPLES_MODE);
        }

        // Pause
        if (game.is_Screen_Menu == false && game.is_Screen_Game_Over == false)
        {
            // Check pressed ESC button
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                game.is_Screen_Pause = !game.is_Screen_Pause;
            }

            // Check mouse position and click on a button
            game.mouse_Position = sf::Mouse::getPosition(window);

            // Continue button
            if (game.ui_state.text_Continue.getGlobalBounds().contains(static_cast<float>(game.mouse_Position.x),
                                                                       static_cast<float>(game.mouse_Position.y)))
            {
                game.ui_state.text_Continue.setFillColor(sf::Color::Green);

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    game.is_Screen_Pause = false;
                }
            }
            else
            {
                game.ui_state.text_Continue.setFillColor(sf::Color::White);
            }

            // Exit button
            if (game.ui_state.text_Exit.getGlobalBounds().contains(static_cast<float>(game.mouse_Position.x),
                                                                   static_cast<float>(game.mouse_Position.y)))
            {
                game.ui_state.text_Exit.setFillColor(sf::Color::Red);

                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    game.is_Screen_Menu = true;
                    game.is_Screen_Pause = false;
                    Init_Game(game);
                }
            }
            else
            {
                game.ui_state.text_Exit.setFillColor(sf::Color::White);
            }
        }
        
        // Leaderboard
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Tab)
            {
                game.is_Leaderboard = true;
                game.ui_state.is_Draw_Pause_Buttons = false;
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Tab)
            {
                window.draw(game.ui_state.text_Continue);
                window.draw(game.ui_state.text_Exit);
                game.ui_state.is_Draw_Pause_Buttons = true;
                game.is_Leaderboard = false;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------
    void Toggle_Game_Mode(SGame& game, const int mode_selection)
    {
        game.game_Mode ^= mode_selection;
    }
    //------------------------------------------------------------------------------------------------------------
    string Get_Button_Text(const SGame& game, const int mode_selection)
    {
        if (game.game_Mode & mode_selection)
        {
            return "On";
        }

        return "Off";
    }
    //------------------------------------------------------------------------------------------------------------
    // Draw window
    void Draw_Game(SGame& game, sf::RenderWindow& window, const sf::Event &event)
    {
        // Draw background
        window.draw(game.game_map_Sprite);

        // Draw player
        Draw_Player(game.player, window);

        // Draw apples
        for (SApple& apple : game.apples_array)
        {
            if (apple.is_Eaten_Apple == false)
            {
                Draw_Apple(apple, window);
            }
        }
        
        // Draw rocks
        for (auto& tree_count : game.trees_array)
        {
            Draw_Tree(tree_count, window);
        }

        // Draw GameOver
        if (game.background.getFillColor() == sf::Color::Red ||
            game.background.getFillColor() == sf::Color::Blue)
        {
            window.draw(game.background);
        }

        // Draw start setting
        Draw_User_Interface(game.ui_state, game, window);
    }
    //------------------------------------------------------------------------------------------------------------
    void Deinitialize_Game(SGame& game)
    {
    }
    //------------------------------------------------------------------------------------------------------------
}
