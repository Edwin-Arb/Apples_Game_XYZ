#pragma once
#include "Constants.h"



namespace Apples_Game
{
    struct SVector_2D
    {
        float X = 0.f;
        float Y = 0.f;
    };

    typedef SVector_2D SPosition_2D;
    inline SVector_2D operator+(const SVector_2D &lhs, const SVector_2D &rhs)
    {
        return {lhs.X + rhs.X, lhs.Y + rhs.Y};
    }

    struct SRectangle
    {
        SPosition_2D position;
        SVector_2D size;
    };

    struct SCircle
    {
        SPosition_2D position;
        float radius;
    };
    
    bool Do_Shapes_Collide(const SRectangle &rect_1, const SRectangle &rect_2);
    bool Do_Shapes_Collide(const SRectangle &rect, const SCircle &circle);
    bool Do_Shapes_Collide(const SCircle &circle_1, const SCircle &circle_2);
    void Check_Collision_With_Apples(struct SGame &game);
    
    SPosition_2D Get_Random_Position_In_Screen(const SRectangle &rect);
    
    void Set_Sprite_Size(sf::Sprite& sprite, const float desired_Width, const float desired_Height);
    void Set_Sprite_Relative_Origin(sf::Sprite& sprite, const float origin_X, const float origin_Y);
    int Get_Random_Int(const int &min, const int &max);
}
