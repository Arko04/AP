#include "gameEntity.hpp"
#include "game.hpp"

int delta_x[4] = {-1, 0, 1, 0};
int delta_y[4] = {0, -1, 0, 1};

void GameEntity::set_sprite(Sprite *_sprite)
{

    sprite = _sprite;
}

void Turtix::move(Direction direction)
{
    int x = sprite->getPosition().x, y = sprite->getPosition().y ;

    int new_x = x + delta_x[direction] * STEP_SIZE;
    int new_y = y + delta_y[direction] * STEP_SIZE;
    if (new_x >= 0 && new_x < 600 && new_y >= 0 && new_y < 600)
    {
        x = new_x;
        y = new_y;
        sprite->setPosition(x, y);
    }
    // sprite->setPosition(sprite->getPosition().x + 10, sprite->getPosition().y);
}

Sprite* GameEntity::get_sprite()
{
    return sprite;
}

void GameEntity::set_texture(Texture* _texture){
    tuxture = _texture;
}

void LiveEntity::tick() 
{

}