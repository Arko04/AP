#pragma once
#include "all.hpp"

class Turtix { 
public:
    void set_jump_status(bool _can_jump){
        can_jump = _can_jump;
    }
    void update(float delta_time, Direction direction);
    void draw(RenderWindow& window);
    Turtix(float speed, float jump_height);

    void set_idle_animaion()
    {
        idle_texture = new Texture;
        //idle_texture = _idle_texture;
        idle_texture->loadFromFile("./sprite/1C5230-removebg-preview.png",IntRect(0,0,480,380));
        idle_texture->setSmooth(true);
        
        
        idle_animation = Animation(idle_texture, Vector2u(5,4), 0.15f, 16);
    }
    // void set_walking_animaion()
    // {
    //    walking_texture = new Texture;
    //    //idle_texture = _idle_texture;
    // walking_texture->loadFromFile("./sprite/1C5230-removebg-preview.png",IntRect(0,0,480,380));
    // walking_texture->setSmooth(true);
    //    idle_animation = Animation(idle_texture, Vector2u(5,4), 0.15f, 16);
    // }
    void set_speeding(bool _Speeding ){
        speeding =_Speeding;
    }
  //  void set_walking_animation(Texture *texture, Vector2u image_count, float switch_time)
    //{
    //    walking_animation = Animation(texture, image_count, switch_time);
    //}
    //void set_jumping_animation(Texture *texture, Vector2u image_count, float switch_time)
    //{
   //     jumping_animation = Animation(texture, image_count, switch_time);
    //}
    Vector2f get_position(){ return body.getPosition();}
    Collision get_collider() {return Collision(body);}
    RectangleShape* get_body(){ return &body;}

    void on_collision(Vector2f direction);

private:
    RectangleShape body;
    //Animation animatuin;
    

    Texture *idle_texture;
    Animation idle_animation; 
    Texture *walking_texture;
     Animation walking_animation;
    // Animation jumping_animation;

    //unsigned int row;
    float speed;
    bool face_right=true;
    double time;
    bool speeding = false;

    Vector2f velocity;
    bool can_jump = false;
    float jump_height;

};
