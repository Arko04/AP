#include <iostream>
#include "game.hpp"

using namespace sf;
using namespace std;


void Game::play()
{
    Clock clock;
    
    window->setFramerateLimit(60);
    while (window->isOpen()){
        window->setVerticalSyncEnabled(true);
        Event event;
        while (window->pollEvent(event))
        {
            switch (event.type){
                case Event::Closed:
                    window->close();
                    break;
                case Event::KeyPressed:
                    switch(event.key.code){
                        case Keyboard::A:
                            handle_move(LEFT);
                            break;
                        case Keyboard::D:
                            handle_move(RIGHT); 
                            break;
                        case Keyboard::Space:
                            // TODO
                            break;
                        
                        case Keyboard::Enter:
                            start();
                            started = true;
                            break;
                    }
            }
        }
        if (clock.getElapsedTime()>=milliseconds(50)){
            tick();
            clock.restart();
        }
        window->display();
    }
}
void Game::start(){
    Texture *texture = new Texture;

    if(!texture->loadFromFile("./sprite/216267_prev_ui.png", IntRect(100, 100, 200, 200))){  
        cerr << "Error loading the file" <<endl;
    }
    Sprite* sprite = new Sprite(*texture);
    turtix.set_sprite(sprite);
    turtix.set_texture(texture);
    sprite->setPosition(400, 400);
    sprite->setScale(0.5f, 0.5f);
    sprite->setTexture(*texture);
    
    window->draw(*sprite);
}

void Game::tick()
{
    if(!started)
        return ;
    //turtix.move();

}
void Game::handle_move(Direction direction){
    turtix.move(direction);
    Sprite* srite = turtix.get_sprite();
    
    
    window->clear();
    window->draw(*srite);
    // window->display();
}
