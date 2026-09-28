#pragma once
#include "all.hpp"
#include "collision.hpp"

Collision::Collision(RectangleShape _body) : body(_body)
{

}

bool Collision::CheckCollision(RectangleShape& other_body, Vector2f* direcction,float push)
{
    Collision* other = new Collision (other_body);
    Vector2f other_position = other->get_position();
    Vector2f other_half_size = other->get_half_size();
    Vector2f this_position = get_position();
    Vector2f this_half_size = get_half_size();

    float delta_x = other_position.x - this_position.x; 
    float delta_y = other_position.y - this_position.y;

    float intersect_x = abs(delta_x) - (other_half_size.x + this_half_size.x);
    float intersect_y = abs(delta_y) - (other_half_size.y + this_half_size.y);

    if(intersect_x < 0.0f && intersect_y < 0.0f)
    {
        push = min(max(push, 0.0f), 1.0f);

        if (intersect_x > intersect_y)  
        {
            if(delta_x > 0.0f)
            {
                Move(intersect_x * (1.0f - push), 0.0f);
                other->Move(-intersect_x * push, 0.0f);
                // hit sth on the right
                direcction->x = 1.0f;
                direcction->y = 0.0f;
            }
            else
            {
                Move(-intersect_x * (1.0f - push), 0.0f);
                other->Move(intersect_x * push, 0.0f);
                // hit sth on the left
                direcction->x = -1.0f;
                direcction->y = 0.0f;
            }
            
        }
        else
        {
            if(delta_y > 0.0f)
            {
                Move(0.0f, intersect_y * (1.0f - push));
                other->Move(0.0f, -intersect_y * push);
                // collide sth underneath
                direcction->x = 0.0f;
                direcction->y = 1.0f;
            }
            else
            {
                Move(0.0f, -intersect_y * (1.0f - push));
                other->Move(0.0f, intersect_y * push);
                // collide sth upward
                direcction->x = 0.0f;
                direcction->y = -1.0f;
            }
        }

        return true;
    }
    // direcction->x = 0;
    // direcction->y = 0;
    return false;
}
