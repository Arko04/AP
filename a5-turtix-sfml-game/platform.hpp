#pragma once
#include "all.hpp"

class Platform
{
public:
    Platform(Texture* texture, Vector2f size, Vector2f position);
    void draw(RenderWindow* window);
    Collision get_collider() { return Collision(body); }
    
private:
    RectangleShape body;
    
};