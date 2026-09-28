#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
// #include <SFML/Window.hpp>

using namespace std;
using namespace sf;

const int MADNESS = 10;
const int STEP_SIZE = 2;

enum Direction
    {
        LEFT,
        UP,
        RIGHT,
    };

class GameEntity{

    private:
        
    protected:
        Sprite* sprite;
        Texture* tuxture;
        //vector <Texture*> textures;
        //int texture_index;
        //bool taken();
        
    public:
        Sprite* get_sprite();
        void set_sprite(Sprite* sprite);
        void set_texture(Texture *texture);
        void draw();

};

class LiveEntity : public GameEntity{
    private:

    protected:

    public:
        // void tick();
        void tick();
        void reverse();
};
class Turtix : public LiveEntity{
    private:

    public:
        //void handle_move(Direction direction);
        void move(Direction Direction);
};
// class Enemy : public LiveEntity{
//     protected:
//     private:
//     public:

// };
// class ChildTurtix : public LiveEntity{
//     public:
//         // void tick();
// };
// class Turtix : public LiveEntity{


// };