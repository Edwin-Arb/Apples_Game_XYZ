#pragma once
#include "Constants.h"

namespace Apples_Game
{
    struct SApple
    {
        bool is_Eaten_Apple = false;
        SPosition_2D position;
        sf::Sprite sprite;

        //struct SApples_Grid_Cell *grid_cells[GRID_SIZE] = {nullptr};git 
        //int num_grid_cells = 0;
    };

    // struct SApples_Grid_Cell
    // {
    //     SApple *ptr_apples[MAX_APPLES_IN_CELL] = {nullptr};
    //     int num_apples_in_cell = 0;
    // };
    //
    // struct SApples_Grid
    // {
    //     SApples_Grid_Cell cells[APPLES_GRID_CELLS_HORIZONTAL][APPLES_GRID_CELLS_VERTICAL] = {};
    // };

    struct SGame;

    void Init_Apple(SApple& apples, const SGame &game);
    SCircle Get_Apple_Collider(const SApple &apple);
    void Reset_Apple_State(SApple &apple, const SGame &game);
    void Draw_Apple(SApple& apple, sf::RenderWindow& window);
    //void Mark_Apple_As_Eaten(SApple &apple);
    
    //void Clear_Apples_Grid(SApples_Grid &apples_grid);
    //void Add_Apple_To_Grid(SApples_Grid &apple_grid, SApple &apple);
    //void Remove_Apple_From_Grid(SApples_Grid& apples_grid, SApple &apple);
    //bool FindPlayerCollisionWithApples(const SVector_2D& player_position, const SApples_Grid& grid, SApple *result[], int& num_found_apples);
}
