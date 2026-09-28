#pragma once
#include "all.hpp"

Animation::Animation()
{

}
Animation::Animation(Texture *_texture, Vector2u _image_count, float _switch_time, int _images_cnt)
{
    // we can get the size of the texture as an argument instead of the whole texture
    this->image_count = _image_count;
    this->switch_time = _switch_time;
    this->images_cnt = _images_cnt;
    total_time = 0.0f;
    current_image.x = 0;
    current_image.y = 0;

    uv_rect.width = _texture->getSize().x / float(image_count.x);
    uv_rect.height = _texture->getSize().y / float(image_count.y);
}
void Animation::update(float delta_time, bool speeding){
    total_time+=delta_time;
    
    if(total_time>=switch_time)
    {
        total_time-=switch_time;
        if (speeding == true)
        {
            current_image.x++;
            image_index++;
        }

        if (current_image.x == image_count.x){
            current_image.x = 0;
            current_image.y++;
        }
        if (image_index==images_cnt)
        {
            current_image.x = 0;
            current_image.y = 0;
            image_index = 0;
        }
    }
    uv_rect.top = current_image.y * uv_rect.height;
    if (face_right)
    {
            uv_rect.left = current_image.x * uv_rect.width;
            uv_rect.width = abs(uv_rect.width);
    }
    else
    {
        uv_rect.left = (current_image.x+1) * abs(uv_rect.width);
        uv_rect.width = -abs(uv_rect.width);
    }

}
void Animation::set_direction(bool _face_right){
    face_right = _face_right;
}
