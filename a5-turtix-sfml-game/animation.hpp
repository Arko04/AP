#pragma once
#include "all.hpp"

class Animation
{
public:
    Animation();
    Animation(Texture *Texture, Vector2u image_count, float switch_time, int images_cnt);
    void update(float delta_time, bool speeding);
    void set_direction(bool _face_right);
    Texture* get_texture(){ return texture; }
    IntRect uv_rect;
private:
    Texture * texture;
    Vector2u image_count;
    Vector2u current_image;

    int image_index = 0;
    int images_cnt;

    float total_time;
    float switch_time;

    bool face_right = true;

};