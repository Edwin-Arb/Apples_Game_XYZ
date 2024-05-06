#include "Apple.h"
#include <cassert>
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
    // void Mark_Apple_As_Eaten(SApple& apple)
    // {
    //     apple.is_Eaten_Apple = true;
    // }
    //--------------------------------------------------------------------------------------------------------
    // void Clear_Apples_Grid(SApples_Grid& apples_grid)
    // {
    //     // Проходим по каждой ячейке сетки по горизонтали
    //     for (unsigned i = 0; i < APPLES_GRID_CELLS_HORIZONTAL; ++i)
    //     {
    //         // Проходим по каждой ячейке сетки по вертикали
    //         for (unsigned j = 0; j < APPLES_GRID_CELLS_VERTICAL; ++j)
    //         {
    //             // Получаем ссылку на текущую ячейку сетки
    //             SApples_Grid_Cell& cell = apples_grid.cells[i][j];
    //
    //             // Проходим по каждому элементу (яблоку) в текущей ячейке
    //             for (unsigned k = 0; k < MAX_APPLES_IN_CELL; ++k)
    //             {
    //                 // Получаем указатель на яблоко в текущей ячейке
    //                 SApple* apple = cell.ptr_apples[k];
    //
    //                 // Если яблоко существует
    //                 if (apple != nullptr)
    //                 {
    //                     // Удаляем указатель на ячейку сетки из списка ячеек, в которых находится яблоко
    //                     for (int i = apple->num_grid_cells - 1; i > 0; --i)
    //                     {
    //                         apple->grid_cells[i] = nullptr;
    //                     }
    //                     // Сбрасываем количество ячеек, в которых находится яблоко
    //                     apple->num_grid_cells = 0;
    //                 }
    //                 // Устанавливаем указатель на яблоко в текущей ячейке в nullptr
    //                 cell.ptr_apples[k] = nullptr;
    //             }
    //             // Сбрасываем количество яблок в текущей ячейке
    //             cell.num_apples_in_cell = 0;
    //         }
    //     }
    // }
    // //--------------------------------------------------------------------------------------------------------
    // void Add_Apple_To_Grid(SApples_Grid& apple_grid, SApple& apple)
    // {
    //     // Вычисляем координаты углов яблока
    //     SVector_2D apple_corner_TL = apple.position + SVector_2D{-APPLE_SIZE / 2, -APPLE_SIZE / 2};
    //     SVector_2D apple_corner_BR = apple.position + SVector_2D{APPLE_SIZE / 2, APPLE_SIZE / 2};
    //
    //     // Вычисляем размеры ячеек сетки по горизонтали и вертикали
    //     constexpr float cell_size_x = static_cast<float>(SCREEN_WIDTH) / APPLES_GRID_CELLS_HORIZONTAL;
    //     constexpr float cell_size_y = static_cast<float>(SCREEN_HEIGHT) / APPLES_GRID_CELLS_VERTICAL;
    //
    //     // Находим индексы минимальной и максимальной ячеек, которые содержат яблоко
    //     const int min_cell_x = std::max(static_cast<int>(apple_corner_TL.X / cell_size_x), 0);
    //     const int max_cell_x = std::min(static_cast<int>(apple_corner_BR.X / cell_size_x),
    //                                     static_cast<int>(APPLES_GRID_CELLS_HORIZONTAL - 1));
    //     
    //     const int min_cell_y = std::max(static_cast<int>(apple_corner_TL.Y / cell_size_y), 0);
    //     const int max_cell_y = std::min(static_cast<int>(apple_corner_BR.Y / cell_size_y),
    //                                     static_cast<int>(APPLES_GRID_CELLS_VERTICAL - 1));
    //
    //     // Добавляем яблоко в новые ячейки
    //     for (int cell_x = min_cell_x; cell_x <= max_cell_x; ++cell_x)
    //     {
    //         for (int cell_y = min_cell_y; cell_y <= max_cell_y; ++cell_y)
    //         {
    //             SApples_Grid_Cell& cell = apple_grid.cells[cell_x][cell_y];
    //
    //             // Проверяем, было ли яблоко уже добавлено в эту ячейку
    //             bool is_apple_in_cell = false;
    //             for (int i = 0; i < apple.num_grid_cells; ++i)
    //             {
    //                 if (apple.grid_cells[i] == &cell)
    //                 {
    //                     is_apple_in_cell = true;
    //                     break;
    //                 }
    //             }
    //
    //             // Если яблоко еще не добавлено в эту ячейку, добавляем его
    //             if (!is_apple_in_cell)
    //             {
    //                 if (cell.num_apples_in_cell < MAX_APPLES_IN_CELL)
    //                 {
    //                     cell.ptr_apples[cell.num_apples_in_cell++] = &apple;
    //                     apple.grid_cells[apple.num_grid_cells++] = &cell;
    //                 }
    //                 else
    //                 {
    //                     // Обработка случая, когда ячейка переполнена
    //                 }
    //             }
    //         }
    //     }
    // }
    // //--------------------------------------------------------------------------------------------------------
    // void Remove_Apple_From_Grid(SApples_Grid& apples_grid, SApple& apple)
    // {
    //     // Проходим по каждой ячейке, в которой находится яблоко
    //     for (int i = 0; i < apple.num_grid_cells; ++i)
    //     {
    //         SApples_Grid_Cell* cell = apple.grid_cells[i];
    //         // Проходим по каждому яблоку в текущей ячейке
    //         for (int j = 0; j < cell->num_apples_in_cell; ++j)
    //         {
    //             // Если находим яблоко, которое нужно удалить, сдвигаем оставшиеся яблоки и уменьшаем количество яблок в ячейке
    //             if (cell->ptr_apples[i] == &apple)
    //             {
    //                 cell->ptr_apples[i] = cell->ptr_apples[cell->num_apples_in_cell - 1];
    //                 cell->num_apples_in_cell--;
    //                 break;
    //             }
    //         }
    //         // Удаляем ссылку на ячейку из массива ячеек яблока
    //         apple.grid_cells[i] = nullptr;
    //     }
    //     // Обновляем количество ячеек, в которых находится яблоко
    //     apple.num_grid_cells = 0;
    // }
    //
    // //--------------------------------------------------------------------------------------------------------
    // bool FindPlayerCollisionWithApples(const SVector_2D& player_position, const SApples_Grid& grid, SApple* result[],
    //                                    int& num_found_apples)
    // {
    //     const SVector_2D player_corner_TL = player_position + SVector_2D{-PLAYER_SIZE / 2, -PLAYER_SIZE / 2};
    //     const SVector_2D player_corner_BR = player_position + SVector_2D{PLAYER_SIZE / 2, PLAYER_SIZE / 2};
    //
    //     constexpr float cell_size_x = static_cast<float>(SCREEN_WIDTH) / APPLES_GRID_CELLS_HORIZONTAL;
    //     constexpr float cell_size_y = static_cast<float>(SCREEN_HEIGHT) / APPLES_GRID_CELLS_VERTICAL;
    //
    //     const int min_cell_x = std::max(static_cast<int>(player_corner_TL.X / cell_size_x), 0);
    //     const int max_cell_x = std::min(static_cast<int>(player_corner_BR.X / cell_size_x),
    //                                     static_cast<int>(APPLES_GRID_CELLS_HORIZONTAL - 1));
    //
    //     const int min_cell_y = std::max(static_cast<int>(player_corner_TL.Y / cell_size_y), 0);
    //     const int max_cell_y = std::min(static_cast<int>(player_corner_BR.Y / cell_size_y),
    //                                     static_cast<int>(APPLES_GRID_CELLS_VERTICAL - 1));
    //
    //     num_found_apples = 0;
    //     for (int cell_x = min_cell_x; cell_x <= max_cell_x; ++cell_x)
    //     {
    //         for (int cell_y = min_cell_y; cell_y <= max_cell_y; ++cell_y)
    //         {
    //             for (int i = 0; i < grid.cells[cell_x][cell_y].num_apples_in_cell; ++i)
    //             {
    //                 SApple* apple = grid.cells[cell_x][cell_y].ptr_apples[i];
    //                 if (!apple->is_Eaten_Apple)
    //                 {
    //                     float dx = player_position.X - apple->position.X;
    //                     float dy = player_position.Y - apple->position.Y;
    //                     float distance = sqrt(dx * dx + dy * dy);
    //                     if (distance < (PLAYER_SIZE + APPLE_SIZE) / 2)
    //                     {
    //                         result[num_found_apples] = apple;
    //                         ++num_found_apples;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    //
    //     return num_found_apples > 0;
    // }
    //--------------------------------------------------------------------------------------------------------
}
