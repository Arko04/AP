#pragma once
#include "all.hpp"

class Collision
{
public:

    Collision(RectangleShape body);
    

    bool CheckCollision(RectangleShape& other_body ,Vector2f* direcction,float push);
    Vector2f get_position() { return body.getPosition();}
    Vector2f get_half_size () { return body.getSize() / 2.0f; }
private:

    RectangleShape body;
    void Move(float dx, float dy){ body.move(dx, dy);}

};