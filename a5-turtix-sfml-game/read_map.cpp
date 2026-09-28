#pragma once
#include "all.hpp"
#include "read_map.hpp"
#include "platform.hpp"


ReadMap::ReadMap(string map_file){
    stringstream input(map_file);
    getline(input, map_file);
    while(getline(input, map_file)){
        string image;
        Vector2f size;
        Vector2f position;
        IntRect int_rect;
        input >> image >> size.x >>size.y >> position.x >> position.y >> int_rect.left >> int_rect.top >> int_rect.width >> int_rect.height;
        Texture *texture;
        texture->loadFromFile(image, int_rect);
        platforms.push_back(Platform(texture, size, position));
    }
}
vector <Platform> ReadMap:: get_platforms(){
    return platforms;
}