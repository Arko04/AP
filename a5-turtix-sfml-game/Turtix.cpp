#pragma once
#include "all.hpp"
#include "Turtix.hpp"
#include "animation.hpp"

using namespace sf;
using namespace std;

Turtix::Turtix(float _speed, float _jump_height)
{
    this->speed = _speed;
    this->jump_height = _jump_height;
    //row = 0;
    //face_right = true;
    
    body.setSize(Vector2f(200.0f, 200.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(200.0f,300.0f); 
    
    ///body.setTexture(texture);
}
void Turtix::on_collision(Vector2f direction)
{
    if(direction.x < 0)
    {
        //  collsion on the left
        velocity.x = 0.0f;
        speeding  = false;
    }
    else if (direction.x > 0)
    {
        //  collsion on the right
        velocity.x = 0.0f;
        speeding = false;
    }
    if(direction.y < 0)
    {
        // collision on the button
        velocity.y = 0.0f;
        can_jump = true;
    }
    else if(direction.y > 0)
    {
        // collision on the button
        velocity.y = 0.0f;
        //can_jump=false;
    }
    // if( direction.x == 0 && direction.y == 0)
    //     can_jump = false;
    else { can_jump = false;}
}
void Turtix::update(float delta_time, Direction direction)
{
    Animation *animatuin;
    Texture *texture;

    velocity.x = 0.0f;

    float cur_speed = (speeding)?speed:0;//
    // Vector2f velocity(0.0f, 0.0f);
    if(direction == UP && can_jump)
    {
        can_jump = false;
        velocity.y = -sqrtf(2.0f * 0.13f * jump_height);
        // velocity.y += cur_speed * delta_time;
    }
    
    if (!can_jump)
        velocity.y += 9.0f * delta_time;
    else{
        velocity.y = 0.0f;
    }

    if(direction == RIGHT)
    {velocity.x += cur_speed * delta_time;
        //idle_animation.set_direction(false); /////should be defined
    }
    // we should check the velocity in y axis
    else if(direction == LEFT)
    {velocity.x -= cur_speed * delta_time;
        //idle_animation.set_direction(true); /////should be defined
    }

    if(velocity.x == 0.0f)// animatuin = idle_animation
    {
        animatuin = &idle_animation;
        texture = idle_texture;
    }
    else
    {
        animatuin = &idle_animation; // it should be walikn anime
        texture = idle_texture;
        if(velocity.x > 0)
            face_right = true;
        else
            face_right = false;
    }
    if(direction == RIGHT)
        {//velocity.x += cur_speed * delta_time;
        animatuin->set_direction(false); /////should be defined
        }

    if(direction == LEFT)
    {//velocity.x -= cur_speed * delta_time;
        animatuin->set_direction(true); /////should be defined
    }
    //Texture *new_texture = idle_animation.get_texture();
    body.setTexture(texture);
    animatuin->update(delta_time, speeding);
    body.setTextureRect(animatuin->uv_rect);
    body.move(velocity);
}

void Turtix::draw(RenderWindow& window)
{
    window.draw(body);
}

// class Game{
//     public:
//     vector< Texture* > textures;
//     vector < GameEntity* > entities;

//     private:

// };
