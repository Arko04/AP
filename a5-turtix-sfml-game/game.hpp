#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "gameEntity.hpp"
using namespace sf;

class Game
{
private:
    RenderWindow* window = new RenderWindow(VideoMode(800, 800), "my window", Style::Close);
    void start();
    void tick();
    void draw(RenderWindow *window);
    bool started = false;
public:
    Turtix turtix;

    void play();
    void handle_move(Direction direction);

    // void update();
    // void render();
};